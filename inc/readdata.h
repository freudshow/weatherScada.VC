#ifndef READDATA_H
#define READDATA_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSettings>
#include <QMap>
#include "basedef.h"
#include "com.h"
#include "logic.h"
#include "db.h"
#include "ui_readdata.h"

#define	TABLE_DEFAULT_ROWS	2
#define	TABLE_COLS			21

typedef enum {
	COL_SEQ = 0		,//序列号
	COL_DATE		,//日期
	COL_TIMENODE	,//时间点
	COL_TEMPIN		,//供水温度
	COL_TEMPOUT		,//回水温度
	COL_TEMPAVG		,//平均温度
	COL_FLOWRATE	,//流速
	COL_POWER		,//功率
	COL_ACCUMFLOW	,//累计流量
	COL_DELTAFLOW	,//流量增量
	COL_ENERGY		,//累积热量
	COL_DELTAENERGY	,//热量增量
	COL_TROOM1		,//室内温度1
	COL_TROOM2		,//室内温度2
	COL_TAIR1		,//室外温度1
	COL_TAIR2		,//室外温度2
	COL_WINDRATE	,//风速
	COL_WFINE		,//晴
	COL_WCLOUDY		,//多云
	COL_WSHADE		,//阴
	COL_ROOMAREA	//房屋建筑面积
} colIdx;

class readDataDlg : public QWidget
{
    Q_OBJECT

public:
    explicit readDataDlg(QWidget *parent = 0);
    ~readDataDlg();


private:
    Ui::readDataForm *ui;

	bool m_comIsOpen;
	uint32 m_seq;//当前行的序列号
	QSettings* m_settings;

	QThread* m_comThread;
	comObject* m_comPort;

	QThread* m_logicThread;
	logicObject* m_logicObj;

	QThread* m_dbThread;
	sqliteDb* m_dbObj;

	QList<QSerialPort::BaudRate>	m_baudList;//绑定顺序与sysconfig中的combox一致, 下同
	QList<QSerialPort::DataBits>	m_databitList;
	QList<QSerialPort::Parity>		m_parityList;
	QList<QSerialPort::StopBits>	m_stopbitList;

	QList<historyDataStr> m_hisDataList;

private slots:
	void showEvent(QShowEvent* e);
	void closeEvent(QCloseEvent* e);
	void initWidget();
	void initCom();
	void initLogic();
	void initDb();
	void initIntraction();//把logic, db, com三个模块的信号槽串联起来

	void on_btnOpenCom_clicked();
	void on_btnReadData_clicked();
	void on_btnSave_clicked();
	void on_btnExit_clicked();
	void resizeEvent(QResizeEvent * event);
	void newTblRow(int);

public slots:
	void getData(historyDataStr);

	void openComOK();
	void openComFail();

	void allDataQueryDone();
	void allDataUpdateDone();

signals:
	void signalClosed();
	void queryData(const QDate start, const QDate end);
	void openCom(comInfoPtr);
	void tblDataDone(QList<historyDataStr>);//表格的每一行的数据都已转成标准历史数据格式
};

#endif // READDATA_H
