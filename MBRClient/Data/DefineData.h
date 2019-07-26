#ifndef DEFINEDATA_H
#define DEFINEDATA_H

#include "ConstData.h"
#include <QMessageBox>
#include "AEyeLog.h"
#include "AEyeDB_Firebird.h"

#define MAX_BLOB_SIZE (60 * 1024)
#define DATA_MAXLENGTH 64*1024

#define safeDelete(p)  { if(p) { delete (p);  (p) = NULL; } }

#define MSGBOX_WARN(text)	      QMessageBox::warning(this, CLIENT_NAME, text)
#define MSGBOX_INFO(text)	          QMessageBox::information(this, CLIENT_NAME, text)
#define MSGBOX_ERROR(text)	      QMessageBox::critical(this, "dsad", text)
#define MSGBOX_QUESTION(text)    QMessageBox::question(this, CLIENT_NAME, text, QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes)
#define MSGBOX_QUESTION2(text)   QMessageBox::question(this, CLIENT_NAME, text, QMessageBox::Ok, QMessageBox::Ok)

#define _MSGBOX_WARN(text)	      QMessageBox::warning(NULL, CLIENT_NAME, text)
#define _MSGBOX_INFO(text)	      QMessageBox::information(NULL, CLIENT_NAME, text)
#define _MSGBOX_ERROR(text)	      QMessageBox::critical(NULL, CLIENT_NAME, text)
#define _MSGBOX_QUESTION(text)   QMessageBox::question(NULL, CLIENT_NAME, text, QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes)

#define LOG_INFO(text)   AEyeLog::instance()->writeDebugLog(text)
#define LOG_ERR(text)    AEyeLog::instance()->writeErrorLog(text)
#define LOG_SQL(text)    AEyeLog::instance()->writeSqlLog(text)

#define DBHELPER AEyeDB_Firebird::instance()

#endif