
/*
 *   Based on 
 *      code by Francesco Giacomini <francesco.giacomini@cnaf.infn.it>
 *        https://forum.nginx.org/read.php?29,283413,283421#msg-283421
 *      other modules from nginx
 *    */

#include <linux/ipv6.h>
#include <openssl/ssl.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_stream.h>
#include <ngx_event.h>
#include <ngx_event_openssl.h>
#include <ngx_stream_ssl_module.h>

static char* ngx_gridproxy_merge_srv_conf(ngx_conf_t* cf, void*, void*);

static ngx_stream_module_t  ngx_gridproxy_module_ctx = {
    NULL,          /* preconfiguration */
    NULL,          /* postconfiguration */
    NULL,          /* create main configuration */
    NULL,          /* init main configuration */
    NULL,          /* create server configuration */
    ngx_gridproxy_merge_srv_conf,    /* merge server configuration */
};

ngx_module_t  ngx_gridproxy_module = {
    NGX_MODULE_V1,
    &ngx_gridproxy_module_ctx,      /* module context */
    NULL,                           /* module directives */
    NGX_STREAM_MODULE,              /* module type */
    NULL,              /* init master */
    NULL,              /* init module */
    NULL,              /* init process */
    NULL,              /* init thread */
    NULL,              /* exit thread */
    NULL,              /* exit process */
    NULL,              /* exit master */
    NGX_MODULE_V1_PADDING
};

static char* ngx_gridproxy_merge_srv_conf(ngx_conf_t* cf, void* p1, void*p2)
{
  ngx_stream_ssl_conf_t *conf = 
      ngx_http_conf_get_module_srv_conf(cf, ngx_gridproxy_module);

  /* avoid unused */
  int delta = (char *)p2 - (char*)p1;
  delta = delta * 2;

  if (conf->ssl.ctx != NULL) {
      X509_STORE *store = SSL_CTX_get_cert_store(conf->ssl.ctx);
      X509_STORE_set_flags(store, X509_V_FLAG_ALLOW_PROXY_CERTS);
  }

  return NGX_CONF_OK;
}
