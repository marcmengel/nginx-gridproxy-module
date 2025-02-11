
This is a module for nginx that turns on OpenSSL support for Grid Proxy certificate authentication. 

It is very minimal, and is all cargo-cult at the moment; based on a discussion and code from the 
mailing list by Francesco Giacomini <francesco.giacomini at cnaf.infn.it>: 
  https://mailman.nginx.org/pipermail/nginx-devel/2019-March/011999.html
With code rework by Brandon White <bjwhite@fnal.gov> 

It should install as described in
   https://www.nginx.com/blog/compiling-dynamic-modules-nginx-plus

Note that this is an all-or-nothing proposition; one accepts SSL connections before any data is 
transferred, so this not switchable by application / URL / location etc.
