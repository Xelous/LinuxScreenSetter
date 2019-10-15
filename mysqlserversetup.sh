# This is just a quick place to throw this, as I'm in the midst of travelling for business
# and without a flash stick
sudo apt update
sudo apt install -y mysql-server
mkdir setupsql
cd setupsql
echo "USE mysql;" > set.sql
echo "ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'root';" >> set.sql
sudo mysql < setupsql/set.sql
sudo shutdown -r now
