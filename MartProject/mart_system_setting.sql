create database martsystem_db default character set utf8;

create table product(
productName varchar(30) not null,
productPrice int not null,
customerPrice int not null,
quantity int);


create table total(
id int not null primary key,
managerTotal int);

insert into total (id, managerTotal) values (1, 0);

create table login_info(
name varchar(30) not null,
id varchar(16) not null,
pw varchar(16) not null,
role varchar(5)
);

create table cart(
productName varchar(30) not null,
customerprice int,
quantity int,
total int);

create table usage_history(
history varchar(10) not null,
date date,
productName varchar(30),
customerprice int,
quantity int,
refund_reason varchar(100)
);