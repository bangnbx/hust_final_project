from bottle import route, run, request
import pymysql.cursors
import sys
import ctypes

fingerPy = ctypes.CDLL('/usr/lib/libfprint.so.0')
fingerPy.fpi_compare_data_bang.argtypes = (ctypes.c_ubyte * 12050, ctypes.c_ubyte * 2418)
fingerPy.fpi_compare_data_bang.restype = ctypes.c_int

@route('/test')
def test():
  connection = pymysql.connect(host='localhost',
      user='root',
      password='rootpassword',
      db='project',
      charset='utf8',
      cursorclass=pymysql.cursors.DictCursor)
  try:
    with connection.cursor() as cursor:
      query = "INSERT INTO `test` VALUES ('This row was inserted by Python')"
      cursor.execute(query)
      connection.commit()
  finally:
    connection.close()

    return 'Hello PI'

@route('/user/new', method='POST')
def new_user():
  post_data = request.body.read()
  finger = request.forms.get('finger')
  connection = pymysql.connect(host='localhost',
      user='root',
      password='rootpassword',
      db='project',
      charset='utf8',
      cursorclass=pymysql.cursors.DictCursor)
  try:
    with connection.cursor() as cursor:
      query = '''INSERT INTO finger_data (username, data) VALUES (%s, %s)'''
      cursor.execute(query, ('bangchtcht', finger))
      connection.commit()
  finally:
    connection.close()
  return 'DONE'


@route('/verify', method = 'POST')
def verify():
  print('Received data')
  #  print(request.body.read())
  # post_data = request.body.read()
  post_data = request.files.get('finger').file.read()
  #  finger = request.forms.get('finger')
  #  print(sys.getsizeof(finger))
  #  print(finger)
  with open('/home/bangcht/projects/project3/new_blob_server.bin', 'wb') as out_file:
    out_file.write(post_data)


  connection = pymysql.connect(host='localhost',
      user='root',
      password='rootpassword',
      db='project',
      charset='utf8',
      cursorclass=pymysql.cursors.DictCursor)
  try:
    with connection.cursor() as cursor:
      query = '''SELECT data FROM finger_data WHERE username = %s'''
      cursor.execute(query, 'bang_new')
      connection.commit()
      enrolled_finger = cursor.fetchone()['data']
  finally:
    connection.close()

  print('Fetched old data')

  data = (ctypes.c_ubyte * 2418)(*[ctypes.c_ubyte(b) for b in post_data])
  enrolled_data = (ctypes.c_ubyte * 12050)(*[ctypes.c_ubyte(b) for b in enrolled_finger])
  a = fingerPy.fpi_compare_data_bang(enrolled_data, data)
  print("Match score:", a)

  return str(a)

run(host='localhost', port=8080)
