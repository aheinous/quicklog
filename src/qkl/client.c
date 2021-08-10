#include "qkl/client.h"
#include <qkl/usr/platform.h>
#include "qkl/encode.h"

void qkl_client_init(qkl_client *client, void *data, int data_size, int num_elems){
    QKL_ASSERT(num_elems * (int)sizeof(qkl_entry) == data_size);
    qkl_lr_buff_init(&client->buff, data, data_size, sizeof(qkl_entry), num_elems);
    client->dropped = 0;
}




void qkl_client_new_entry(qkl_client *client, const char *fmt, uint8_t *data, int len){

    if(client->dropped && qkl_lr_buff_left_avail(&client->buff)){
        int dropped = client->dropped;
        client->dropped = 0;
        QKL_PRINTF_ENCODE(qkl_client_new_entry, client,
            "<%d msg%s dropped>\n", dropped, dropped==1? "":"s");
    }


    qkl_entry *ent = (qkl_entry *) qkl_lr_buff_left_get(&client->buff);
    if(!ent){
        client->dropped++;
        return;
    }
    ent->fmt = fmt;

    for(int i=0; i<len; i++){
        uint8_t v = data[i];
        ent->data[i] = v;
    }
    qkl_lr_buff_left_put(&client->buff);
}
