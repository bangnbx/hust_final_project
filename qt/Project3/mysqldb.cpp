#include "mysqldb.h"


int init_mysql(MYSQL *mysql) {

  if (mysql_init(mysql) == NULL) {
    printf("\nInitialization error\n");
    return 2;
  }
//  if (mysql_real_connect(mysql, "bangcht.me", "root", "bayogogo",
//            "project", 3306, NULL, 0) == NULL)
  if (mysql_real_connect(mysql, "localhost", "root", "rootpassword",
            "project", 3306, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(mysql));
        mysql_close(mysql);
        printf("Error when init mysql\n");
        return 2;
    }

  return 0;
}

void real_string(char *des, unsigned char *data, int len) {
  MYSQL con;
  init_mysql(&con);
  int escaped_size = 2 * len + 1;
  char chunk[escaped_size];
  mysql_real_escape_string(&con, des, (const char*)data, len);
}

int save_data_to_db(unsigned char *data, size_t data_size, char *username)
{


  MYSQL con;
  init_mysql(&con);

  // done

  // insert
  int escaped_size = 2 * data_size + 1;
  char chunk[escaped_size];
  mysql_real_escape_string(&con, chunk, (const char*)data, data_size);
  const char* query_template =  "INSERT INTO finger_data(username, data, data_size) VALUES ('%s', '%s', '%d')";
  size_t template_len = strlen(query_template);
  int query_buffer_len = template_len + escaped_size + strlen(username) + sizeof(data_size);
  char query[query_buffer_len];
  // testAPI(chunk);
  int query_len = snprintf(query, query_buffer_len, query_template, username, chunk, data_size);

  if (mysql_real_query(&con, query, query_len))
  {
    printf("Something went wrong when INSERT");
    return 2;
  }

  mysql_close(&con);
  return 0;
}
