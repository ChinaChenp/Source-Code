#!/bin/sh

if [ $# != 2 ];then
	echo "use : ./package.sh 3.0.0 119"
	exit -1
fi

make
/home/w/script/rpmbuild2  ./basetool.spec $1 $2 /home/w/
