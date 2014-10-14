Welcome to Mango Framework
====================================

Mango Framework is a Hack framework which provides a set of tools and APIs
to develop high level web services and sites.

Mango is fully object oriented and follows strong MVC patters which allows
your project to scale while retaining maintainability.

Mango also has a powerful Object Relational Mapper (ORM) which allows you
to create complex data structures and APIs without ever having to touch
the database or manage any SQL manually.

Requirements
------------------------------------
Mango Framework is currently supported on Debian 7.6 or later. Other
platforms may work but have not been tested.

In order to run the Mango installer you'll need to have `sudo` and
`hhvm` installed.

Mango Framework will work with both Nginx and Apache. Other web servers may
be supported but have not yet been tested.

Having a web server installed is not required as Mango can be used to create
command line applications as well as web services. If you're planning on
creating a web service with mango however, you will most likely want to use
Nginx or Apache.

Installing Dependencies
------------------------------------

1. First make sure you have `sudo` installed. If you don't, simply follow the steps outline [here](http://www.ducea.com/2006/05/18/install-sudo-on-debian/)
 
2. Let's also install `unzip` so that the mango installer can expand it's packages, we can install it with:

 `$ sudo apt-get install unzip`

3. Next, let's install `hhvm`. Please follow the steps outlined [here](https://github.com/facebook/hhvm/wiki/Prebuilt-Packages-on-Debian-7)

Installing Mango
------------------------------------

Once all the dependencies have been installed, installing Mango itself is easy!
Simply open a new Terminal window and type in the following:

 `$ curl -L https://github.com/jaderfeijo/mango-framework/raw/master/install | sudo hhvm`

This will download the latest version of the install script and install Mango in the `/usr/lib/mango`
directory as well as create a symlink to the `mango` command line utility at `/usr/bin/mango`

You can also specify a certain branch to install from. For example, if you wish to install
the `development` version of Mango, simply specify `development` as the last parameter as
demonstrated below:

 `$ curl -L https://github.com/jaderfeijo/mango-framework/raw/master/install | sudo hhvm development`

Uninstalling
------------------------------------

To uninstall mango simply type:

 `$ curl -L https://github.com/jaderfeijo/mango-framework/raw/master/uninstall | sudo hhvm`

This will remove all Mango Framework files from your system

Donate
------------------------------------

If you find this software useful please don't forget to donate!

Bitcoin: `14j8rsDX238cxTgcW9EBDFK6eY43WA2P9V`

PayPal: jader.feijo@gmail.com

Thank you for using Mango Framework!

We hope you enjoy it!
