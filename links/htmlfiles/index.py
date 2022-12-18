# Import modules for CGI handling 
import cgi, cgitb , sys

# print(sys.argv[1]);

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
print ("<h2>First Name: %s</h2>" % (first_name))
print ("<h2>Last  Name: %s</h2>" % (last_name))
print ("</body>")
print ("</html>")