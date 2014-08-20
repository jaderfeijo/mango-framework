#!/bin/bash

# install ngynx
sudo apt-get update
sudo apt-get install -y python-software-properties
add-apt-repository -y ppa:nginx/stable
sudo apt-get update
sudo apt-get install -y nginx

# install hack
wget -O - http://dl.hhvm.com/conf/hhvm.gpg.key | sudo apt-key add -
echo deb http://dl.hhvm.com/debian wheezy main | sudo tee /etc/apt/sources.list.d/hhvm.list
sudo apt-get update
sudo apt-get install -y hhvm

# install mysql
sudo apt-get update
sudo apt-get install -y mysql-server

# install pathogen.vim
mkdir -p ~/.vim/autoload ~/.vim/bundle && \
curl -LSso ~/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim

# install vim-hack
cd ~/.vim/bundle
git clone git://github.com/hhvm/vim-hack.git