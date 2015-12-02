##############################################################
# http://www.rpm.org/max-rpm/ch-rpm-inside.html              #
##############################################################
Name:%(echo basetool${SUFFIX})
#
Version:%{_version}
Release:%{_release}
Summary: basetool
URL: %{_svn_path}
Group: adplatform
License: adplatform
AutoReq: no
#Requires: 

%description
# if you want publish current svn URL or Revision use these macros
cpmplugin
%{_svn_path}
%{_svn_revision}

# prepare your files
%install
# OLDPWD is the dir of rpm_create running
# _prefix is an inner var of rpmbuild,
# can set by rpm_create, default is "/home/w"
# _lib is an inner var, maybe "lib" or "lib64" depend on OS
# create dirs

mkdir -p $PWD/%{_prefix}/lib64/
mkdir -p $PWD/%{_prefix}/include/basetool/
#mkdir -p $PWD/%{_crondir}/

# copy files
cp -rf $OLDPWD/*.h     	       $PWD/%{_prefix}include/basetool/
cp -rf $OLDPWD/libbasetool.so  $PWD/%{_prefix}lib64/

%post
/sbin/ldconfig

# package infomation
%files
# set file attribute here
#%defattr(755,root,root)
# need not list every file here, keep it as this
# set file attribute here
#%defattr(644,root,root)
%attr(755,root,root) %{_prefix}lib64/

#%dir
# need not list every file here, keep it as this
%{_prefix}

# create an empy dir
# need bakup old config file, so indicate here
# indicate the dir for crontab

%changelog 
