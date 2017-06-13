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
  national_id = request.headers.get('id')
  password = request.headers.get('password')
  name = request.headers.get('name')
  address = request.headers.get('address')
  phone = request.headers.get('phone')
  gender = request.headers.get('gender')

  #  print(national_id)
  #  print(password)
  #  print(name)
  #  print(address)
  #  print(phone)
  #  print(gender)
  post_data = request.files.get('finger').file.read()

  connection = pymysql.connect(host='localhost',
      user='root',
      password='rootpassword',
      db='project',
      charset='utf8',
      cursorclass=pymysql.cursors.DictCursor)

  try:
    with connection.cursor() as cursor:
      query = '''SELECT national_id FROM user WHERE national_id = %s'''
      cursor.execute(query, national_id)
      connection.commit()
      enrolled_finger = cursor.fetchone()
  except Exception as e:
    print(e)

  if enrolled_finger is not None:
    return str(-1)


  try:
    with connection.cursor() as cursor:
      query = '''INSERT INTO user (national_id, password, name, gender, address, phone, finger_data) VALUES (%s, PASSWORD(%s), %s, %s, %s, %s, %s)'''
      cursor.execute(query, (national_id, password, name, gender, address, phone, post_data))
      connection.commit()
  except Exception as e:
    print(e)
  return '0'


@route('/user/verify', method = 'POST')
def verify():
  print('Received data')
  #  print(request.body.read())
  # post_data = request.body.read()
  post_data = request.files.get('finger').file.read()
  national_id = request.headers.get('id')
  password = request.headers.get('password')
  print(national_id)
  print(password)
  #  finger = request.forms.get('finger')
  #  print(sys.getsizeof(finger))
  #  print(finger)
  #  with open('/home/bangcht/projects/project3/new_blob_server.bin', 'wb') as out_file:
    #  out_file.write(post_data)


  connection = pymysql.connect(host='localhost',
      user='root',
      password='rootpassword',
      db='project',
      charset='utf8',
      cursorclass=pymysql.cursors.DictCursor)
  try:
    with connection.cursor() as cursor:
      query = '''SELECT finger_data FROM user WHERE national_id = %s AND password = PASSWORD(%s)'''
      cursor.execute(query, (national_id, password))
      connection.commit()
      enrolled_finger = cursor.fetchone()
  except Exception as e:
    print(e)

  print('Fetched old data')
  if enrolled_finger is not None:
    enrolled_finger = enrolled_finger['finger_data']
  else:
    return '-404'


  data = (ctypes.c_ubyte * 2418)(*[ctypes.c_ubyte(b) for b in post_data])
  enrolled_data = (ctypes.c_ubyte * 12050)(*[ctypes.c_ubyte(b) for b in enrolled_finger])
  a = fingerPy.fpi_compare_data_bang(enrolled_data, data)
  print("Match score:", a)

  if a > 40:
    return str(1)
  else:
    return str(-401)

run(host='localhost', port=8080)
