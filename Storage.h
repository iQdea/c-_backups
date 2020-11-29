#pragma once

/**
	Интерфейс Стратегии объявляет операции, общие для всех поддерживаемых версий
	некоторого алгоритма.
	
	Контекст использует этот интерфейс для вызова алгоритма, определённого
	Конкретными Стратегиями.
*/
class Backup;
class RestorePoint;

class Storage
{
public:
	virtual ~Storage() {}
	virtual void save(Backup& backup) = 0;
	virtual void save(RestorePoint& restorePoint) = 0;
};
