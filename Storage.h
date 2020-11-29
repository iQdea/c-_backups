#pragma once

/**
	��������� ��������� ��������� ��������, ����� ��� ���� �������������� ������
	���������� ���������.
	
	�������� ���������� ���� ��������� ��� ������ ���������, ������������
	����������� �����������.
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
