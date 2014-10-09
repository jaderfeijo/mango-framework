#!/bin/bash

# install basics
echo '****************** Installing basics ******************'
sudo apt-get update
sudo apt-get install -y unzip git curl wget build-essential
sudo apt-get install -y python-software-properties --force-yes

# install nginx
echo '****************** Installing nginx ******************'
sudo apt-get install -y nginx

# install hhvm
echo '****************** Installing hhvm ******************'
sudo add-apt-repository -y ppa:mapnik/boost
wget -O - http://dl.hhvm.com/conf/hhvm.gpg.key | sudo apt-key add -
echo deb http://dl.hhvm.com/debian wheezy main | sudo tee /etc/apt/sources.list.d/hhvm.list
sudo apt-get update
sudo apt-get install -y libmemcached-dev
sudo apt-get install -y --force-yes hhvm
sudo /usr/share/hhvm/install_fastcgi.sh
sudo /etc/init.d/hhvm restart
sudo /etc/init.d/nginx restart
sudo update-rc.d hhvm defaults
cat <<EOM > /etc/nginx/sites-available/hhvm.conf
server {
  server_name hhvm.dev;

  root /var/www;
  index index.php;

  location ~ \.(hh|php)$ {
    fastcgi_pass 127.0.0.1:9000;
    fastcgi_index index.php;
    fastcgi_param SCRIPT_FILENAME /var/www$fastcgi_script_name;
    include fastcgi_params;
  }
}
EOM
sudo rm /etc/nginx/sites-enabled/*
sudo ln -s /etc/nginx/sites-available/hhvm.conf /etc/nginx/sites-enabled/hhvm.conf
sudo service nginx restart

# install vim
echo '****************** Installing vim ******************'
sudo apt-get update
sudo apt-get install -y vim

# install codeschool theme into vim
echo '****************** Installing codeschool theme ******************'
sudo mkdir -p /home/vagrant/.vim/colors
sudo curl https://raw.githubusercontent.com/29decibel/codeschool-vim-theme/master/colors/codeschool.vim > /home/vagrant/.vim/colors/codeschool.vim
sudo echo 'syntax on' >> /home/vagrant/.vimrc
sudo echo 'set nowrap' >> /home/vagrant/.vimrc
sudo echo 'set nu' >> /home/vagrant/.vimrc
sudo echo 'set tabstop=4' >> /home/vagrant/.vimrc
sudo echo 'colorscheme codeschool' >> /home/vagrant/.vimrc
sudo echo 'filetype plugin indent on' >> /home/vagrant/.vimrc

# install pathogen.vim
echo '****************** Installing pathogen ******************'
sudo mkdir -p /home/vagrant/.vim/autoload /home/vagarant/.vim/bundle && \
sudo curl -LSso /home/vagrant/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim
sudo echo 'execute pathogen#infect()' >> /home/vagrant/.vimrc

# install vim-hack
echo '****************** Installing vim-hack ******************'
sudo mkdir -p /home/vagrant/.vim/bundle
cd /home/vagrant/.vim/bundle
sudo git clone git://github.com/hhvm/vim-hack.git

# setup mango-framework
echo '****************** Setting up Mango-Framework  ******************'
cd /vagrant
sudo ./install -y

# finish up
echo '****************** Finishing up ******************'
sudo echo 'cd /vagrant' >> /home/vagrant/.bashrc
echo "All done!"
