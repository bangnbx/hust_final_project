#ifndef MYSQLDB_H
#define MYSQLDB_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mysql/mysql.h>
int init_mysql(MYSQL *mysql);
int save_data_to_db(unsigned char *data, size_t data_size, char *username);
void real_string(char *des, unsigned char *str, int len);
#endif // MYSQLDB_H
