#!/bin/bash

# install basics
echo '****************** Installing basics ******************'
sudo apt-get update
sudo apt-get install -y unzip git curl wget build-essential
sudo apt-get install -y python-software-properties --force-yes

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
sudo update-rc.d hhvm defaults

# install vim
echo '****************** Installing vim ******************'
sudo apt-get update
sudo apt-get install -y vim

# install codeschool theme into vim
echo '****************** Installing codeschool theme ******************'
sudo mkdir -p /home/vagrant/.vim/colors
sudo curl https://raw.githubusercontent.com/29decibel/codeschool-vim-theme/master/colors/codeschool.vim > /home/vagrant/.vim/colors/codeschool.vim
sudo echo 'syntax on' >> /usr/share/vim/vimrc
sudo echo 'set nowrap' >> /usr/share/vim/vimrc
sudo echo 'set nu' >> /usr/share/vim/vimrc
sudo echo 'set tabstop=4' >> /usr/share/vim/vimrc
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
