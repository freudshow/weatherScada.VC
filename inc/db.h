#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include "basedef.h"

#define DB_PATH		"db/hisdata.db"
#define HIS_TABLE	"t_history_data"
#define F_TIMENODE	"f_timenode"


typedef enum {
	FIELD_SEQ = 0,	//序列号
	FIELD_DATE,		//插入时间
	FIELD_TIMENODE,	//时间点
	FIELD_TEMPIN,	//供水温度
	FIELD_TEMPOUT,	//回水温度
	FIELD_TEMPAVG,	//平均温度
	FIELD_FLOWRATE,	//流速
	FIELD_POWER,	//功率
	FIELD_ACCUMFLOW,//累计流量
	FIELD_DELTAFLOW,//流量增量
	FIELD_ENERGY,	//累积热量
	FIELD_DELTAENERGY,//热量增量
	FIELD_TROOM1,	//室内温度1
	FIELD_TROOM2,	//室内温度2
	FIELD_TAIR1,	//室外温度1
	FIELD_TAIR2,	//室外温度2
	FIELD_WINDRATE,	//风速
	FIELD_WEATHER,	//晴
	FIELD_ROOMAREA	//房屋建筑面积
} fieldIdx;

class sqliteDb : public QObject
{
	Q_OBJECT

public:
	sqliteDb(QObject* parent = 0);
	~sqliteDb();

private:
	QSqlDatabase m_sqlDb;

signals:
	void finished();
	void oneRowExist(historyDataStr);
	void oneRowNotExist(sysTimeStr);

	void insertOK();
	void insertFail(sysTimeStr);

	void updateOK();
	void updateFail();

public slots:
	void startThread();

	void queryOneRow(sysTimeStr);
	void insertOneRow(historyDataStr);
	void updateOneRow(historyDataStr);

private slots:
	bool openDB();
	void closeDB();
	int rowCnt(sysTimeStr);
	bool insertIntoDb(historyDataStr hisData);
	bool updateIntoDb(historyDataStr hisData);
};

#endif // DB_H
