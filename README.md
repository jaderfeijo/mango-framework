Welcome to Mango Framework
====================================

Mango Framework a HACK framework which provides a set of tools and APIs
to develop high level web services and web sites.

Mango is fully object oriented and follows strong MVC patters which allows
your project to scale while retaining maintainability.

Mango also has a powerful Object Relational Mapper (ORM) which allows you
to create complex data structures and APIs without ever having to touch
the database or manage any SQL manually.

Requirements
------------------------------------
Mango Framework is supported on both Mac OS X 10.9 and Debian 7.6. Other
platforms may work but have not been tested.

In order to run Mango you'll need the following installed on your system:

* hhvm
* sudo
* apigen

Mango Framework will work with both Nginx and Apache. Other web servers may
be supported but have not been tested.

Installing
------------------------------------

Installing Mango is easy! Simply open a new Terminal window and type in
the following:

 `$ curl -L https://github.com/jaderfeijo/mango-framework/raw/installer/install | bash /dev/stdin`

This will download the latest version of the install script and install Mango in the `/usr/lib/mango`
path as well as create a symlink to the `mango` command line utility at `/usr/bin/mango`

You can also specify a certain branch to install from. For example, if you wish to install
the `development` version of Mango, simply specify `development` as the last parameter as
demonstrated below:

 ` $ curl -L https://github.com/jaderfeijo/mango-framework/raw/installer/install | bash /dev/stdin development`

Uninstalling
------------------------------------

To uninstall mango simply type:

 `$ curl -L https://github.com/jaderfeijo/mango-framework/raw/installer/uninstall | bash /dev/stdin`
 
This will remove all Mango Framework files from your system

Donate
------------------------------------

If you find this software useful please don't forget to donate!

Bitcoin: `14j8rsDX238cxTgcW9EBDFK6eY43WA2P9V`

PayPal: jader.feijo@gmail.com

Thank you for using Mango Framework!

We hope you enjoy it!
