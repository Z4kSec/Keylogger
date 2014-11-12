#!/bin/sh
## sql_conf.sh for  in /home/ouroub_a/spider-2017-krier_g/Server
##
## Made by amina ourouba
## Login   <ouroub_a@epitech.net>
##
## Started on  Tue Nov  4 14:16:46 2014 amina ourouba
## Last update Sat Nov  8 09:31:04 2014 amina ourouba
##

echo -e "\e[0;32mStarting MySQL DB service \e[0;31m(this command might ask for the root password)...\e[0m"
echo -e "\e[0;34msudo /etc/init.d/mysql start\e[0m"
sudo /etc/init.d/mysql start
echo ""
echo -e "\e[0;32mCreating DB & tables. If you did not set any password for MySQL's root user, just leave empty:\e[0m"
mysql -u root -p < ./scripts/db.sql
