
This is a module for nginx that turns on OpenSSL support for Grid Proxy certificate authentication. 

It is very minimal, composed by @marcmengel and is all cargo-cult at the moment; based on a [discussion and code](https://mailman.nginx.org/pipermail/nginx-devel/2019-March/011999.html) discussion and code from the mailing list by @GiacominiFrancesco, with code rework by @bjwhite-fnal.

It should install as described in
   https://www.nginx.com/blog/compiling-dynamic-modules-nginx-plus

Note that this is an all-or-nothing proposition; one accepts SSL connections before any data is 
transferred, so this not switchable by application / URL / location etc.
