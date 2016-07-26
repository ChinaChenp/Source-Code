##############################################################
# http://www.rpm.org/max-rpm/ch-rpm-inside.html              #
##############################################################
Name:%(echo threadpool${SUFFIX})
#

Version:%{_version}
Release:%{_release}
Summary:threadpool 
URL: %{_svn_path}
Group: adplatform
License: adplatform
AutoReq: no
Requires: gmock >= 1.7.0 gtest >= 1.0.0
BuildRequires: gmock >= 1.7.0 gtest >= 1.0.0 

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


mkdir -p $PWD/%{_prefix}/include/
mkdir -p $PWD/%{_prefix}/lib64/
mkdir -p $PWD/%{_prefix}/include/threadpool/
mkdir -p $PWD/%{_prefix}/include/threadpool/example/
#mkdir -p $PWD/etc/ld.so.conf.d/
#mkdir -p $PWD/%{_prefix}/../../../etc/ld.so.conf.d/

# copy files
cp -rf $OLDPWD/inc/* $PWD/%{_prefix}/include/threadpool/
cp -rf $OLDPWD/example/* $PWD/%{_prefix}/include/threadpool/example/
cp -rf $OLDPWD/lib/* $PWD/%{_prefix}/lib64/

%post
/sbin/ldconfig

# package infomation
%files

# set file attribute here
#%defattr(755,root,root)
# need not list every file here, keep it as this
# set file attribute here
#%defattr(644,root,root)
#%attr(755,root,root) %{_prefix}/adserver/bin/*
#%attr(755,root,root) %{_prefix}/adplatform/adserver/conf/*
%attr(755,root,root) %{_prefix}/lib64/libthreadpool.a
%attr(755,root,root) %{_prefix}/lib64/libthreadpool.so
#%attr(755,root,root) /etc/ld.so.conf.d/

#%dir
# need not list every file here, keep it as this
%{_prefix}

# create an empy dir
# need bakup old config file, so indicate here
# indicate the dir for crontab

%changelog 
