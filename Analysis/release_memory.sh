USER_NAME=$(whoami)
condor_qedit -owner $USER_NAME RequestMemory=8192
condor_release user $USER_NAME
