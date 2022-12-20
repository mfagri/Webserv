# #!/usr/bin/python

# import cgi, os
# import cgitb; cgitb.enable()

# form = cgi.FieldStorage()

# # Get filename here.
# fileitem = form['filename']

# Test if the file was uploaded
# !/usr/bin/python
# Import modules for CGI handling
import cgi, cgitb
# Create instance of FieldStorage
form = cgi.FieldStorage()
# Get data from fields
first_name = form.getvalue('first_name')
last_name  = form.getvalue('last_name')
print ("<html>")
print ("<head>")
print ("<title>Hello - Second CGI Program</title>")
print ("</head>")
print ("<body>")
print ("<h2>Hello King  %s %s</h2>" % (last_name,first_name ))
print ("</body>")
print ("</html>")