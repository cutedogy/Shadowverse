#include "sqliteoperator.h"

SqliteOperator::SqliteOperator()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
        {
            database = QSqlDatabase::database("qt_sql_default_connection");
        }
        else
        {
            // 建立和SQlite数据库的连接
            database = QSqlDatabase::addDatabase("QSQLITE");
            // 设置数据库文件的名字
            database.setDatabaseName("MyDataBase.db");
        }
}

// 打开数据库
bool SqliteOperator::openDb()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
      //  printf("SHIT");
    }

    return true;
}
// 创建数据表
void SqliteOperator::createTable2(){
    QSqlQuery sqlQuery;
    QString createSql = QString("CREATE TABLE ROAD (\
                          id INT PRIMARY KEY NOT NULL,\
                          start TEXT NOT NULL,\
                          dest TEXT NOT NULL,\
                          length INT NOT NULL)");
            sqlQuery.prepare(createSql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}
void SqliteOperator::createTable()
{
    // 用于执行sql语句的对象
    QSqlQuery sqlQuery;
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE BJTU (\
                          id INT PRIMARY KEY NOT NULL,\
                          name TEXT NOT NULL,\
                          intro TEXT NOT NULL)");
    sqlQuery.prepare(createSql);
    // 执行sql语句
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

// 判断数据库中某个数据表是否存在
bool SqliteOperator::isTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}
QString SqliteOperator::introduction(int s)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM BJTU");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();

    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            QString intro = sqlQuery.value(2).toString();
            if(id==s){
                return intro;
            }
        }
    }
}

QString SqliteOperator::search(int s)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM BJTU");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();

    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            QString intro = sqlQuery.value(2).toString();
            if(id==s){
                return name;
            }
        }
    }
}
// 查询全部数据
void SqliteOperator::queryTable()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM BJTU");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            QString intro = sqlQuery.value(2).toString();
            qDebug()<<QString("id:%1    name:%2    introduce:%3").arg(id).arg(name).arg(intro);
        }
    }
}
void SqliteOperator::InsertRoadData(road &roadData){
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO ROAD VALUES(:id,:start,:dest,:length)");
    sqlQuery.bindValue(":id", roadData.id);
    sqlQuery.bindValue(":start", roadData.start);
    sqlQuery.bindValue(":dest", roadData.dest);
    sqlQuery.bindValue(":length",roadData.length);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        printf("Ohhhh");
    }
}
void SqliteOperator::singleInsertData(w2dba &singledb)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO BJTU VALUES(:id,:name,:intro)");
    sqlQuery.bindValue(":id", singledb.id);
    sqlQuery.bindValue(":name", singledb.name);
    sqlQuery.bindValue(":intro", singledb.intro);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        printf("Ohhhh");
    }
}
// 插入多条数据
void SqliteOperator::moreInsertData(QList<w2dba>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO BJTU VALUES(?,?,?)");
    QVariantList idList,nameList,introList;
    for(int i=0; i< moredb.size(); i++)
    {
        idList <<  moredb.at(i).id;
        nameList << moredb.at(i).name;
        introList << moredb.at(i).intro;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(nameList);
    sqlQuery.addBindValue(introList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
}
// 修改数据
void SqliteOperator::modifyRoadData(int id, QString start, QString dest, int length){
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE ROAD SET start=?,dest=?,length=? WHERE id=?");
    sqlQuery.addBindValue(start);
    sqlQuery.addBindValue(dest);
    sqlQuery.addBindValue(length);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}
void SqliteOperator::modifyData(int id, QString name, QString intro)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE BJTU SET name=?,intro=? WHERE id=?");
    sqlQuery.addBindValue(name);
    sqlQuery.addBindValue(intro);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

// 删除数据
void SqliteOperator::deleteData(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM BJTU WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}
//删除数据表
void SqliteOperator::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}
void SqliteOperator::closeDb(void)
{
    database.close();
}
