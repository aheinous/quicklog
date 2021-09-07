#include "qkl/server.h"

#include <qkl_usr_platform.h>

#include "qkl/client.h"
#include "qkl/decode.h"
#include "qkl/entry.h"

static qkl_client *clients[QKL_MAX_CLIENTS];
static const char *client_names[QKL_MAX_CLIENTS];
static int num_clients = 0;


#if QKL_USR_SYNC_PRIMITIVES_PROVIDED
static qkl_usr_mutex mutex;
static qkl_usr_cond cycle_cond;
#endif

void qkl_init() {
	qkl_usr_mutex_init(&mutex);
	qkl_usr_cond_init(&cycle_cond);
}

void qkl_reg(qkl_client *client, const char *name) {
	qkl_usr_mutex_lock(&mutex);
	QKL_ASSERT(num_clients < QKL_MAX_CLIENTS);

	clients[num_clients] = client;
	client_names[num_clients] = name;

	num_clients++;
	qkl_usr_mutex_unlock(&mutex);
}


static inline void _wait_one_process_cycle() {
	qkl_usr_cond_wait(&cycle_cond, &mutex);
}

static inline void _flush_client_buffer(qkl_client *client) {
	while(qkl_lr_buff_right_avail(&client->buff)) {
		_wait_one_process_cycle();
	}
}

// called while already holding mutex
static inline void _flush(qkl_client *client) {
#if QKL_USR_SYNC_PRIMITIVES_PROVIDED
	_flush_client_buffer(client);
	if(client->dropped) {
		// dummy msg to make dropped msgs notifications go through
		qkl_client_new_entry(client, "", NULL, 0);
		_flush_client_buffer(client);
	}
#else
	(void)client;
	qkl_process();
#endif
}

void qkl_unreg(qkl_client *client) {
	qkl_usr_mutex_lock(&mutex);

	_flush(client);

	for(int i = 0; i < num_clients; i++) {
		if(clients[i] == client) {
			clients[i] = clients[num_clients - 1];
			client_names[i] = client_names[num_clients - 1];

			num_clients--;
			goto success;
		}
	}
	QKL_ASSERT(0);

success:
	qkl_usr_mutex_unlock(&mutex);
}


void qkl_process() {
	qkl_usr_mutex_lock(&mutex);

	for(int i = 0; i < num_clients; i++) {
		while(1) {
			qkl_entry *ent = (qkl_entry *)qkl_lr_buff_right_get(&clients[i]->buff);
			if(!ent) {
				break;
			}
			// skip dummy msgs
			if(ent->fmt[0] == '\0') {
				continue;
			}

			char s[128];
			int written = qkl_snprintf(s, sizeof(s), "[%s]: ", client_names[i], s);
			qkl_printf_decode(s + written, sizeof(s) - written, ent->fmt, ent->data);
			qkl_lr_buff_right_put(&clients[i]->buff);
			qkl_usr_log_out(s);
		}
	}
	qkl_usr_cond_broadcast(&cycle_cond);
	qkl_usr_mutex_unlock(&mutex);
}
