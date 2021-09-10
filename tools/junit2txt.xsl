<?xml version="1.0" encoding="utf-8"?>
<!--
Source: https://raw.githubusercontent.com/lhotari/travis-gradle-test-failures-to-console/master/travis/junit-xml-format-errors.xsl
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text" indent="no"/>
  <xsl:template match="/testsuite">
  <xsl:text>Testsuite: </xsl:text><xsl:value-of select="@name" />
<xsl:text>
Tests run: </xsl:text>
    <xsl:value-of select="@tests" />
    <xsl:text>, Failures: </xsl:text>
    <xsl:value-of select="@failures" />
    <xsl:text>, Errors: </xsl:text>
    <xsl:value-of select="@errors" />
    <xsl:text>, Time elapsed: </xsl:text>
    <xsl:value-of select="@time" />
    <xsl:text> sec</xsl:text>
    <xsl:apply-templates select="testcase" />
  </xsl:template>

  <xsl:template match="testcase">
    <xsl:text>
Testcase: </xsl:text>
    <xsl:value-of select="@name" />
    <xsl:text> took </xsl:text>
    <xsl:value-of select="@time" />
    <xsl:choose>
      <xsl:when test="failure"><xsl:text> FAILURE</xsl:text></xsl:when>
      <xsl:when test="error"><xsl:text> ERROR</xsl:text></xsl:when>
      <xsl:otherwise><xsl:text> SUCCESS</xsl:text></xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>
