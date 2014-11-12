#include "Hardware.h"

Hardware::Hardware(int idHook) :
_idHook(idHook)
{
	reset();
}

bool Hardware::hook(HOOKPROC lpfn)
{
	if ((_handler = SetWindowsHookEx(_idHook, lpfn, NULL, 0)) == NULL)
		return false;
	return true;
}

void Hardware::unHook()
{
	UnhookWindowsHookEx(_handler);
}

/*
** Setters
*/

void				Hardware::startWorking(const std::string &time)
{
	_isWorking = true;
	_startTime = time;
}

void				Hardware::endWorking(const std::string &time)
{
	_isWorking = false;
	_endTime = time;
}

void				Hardware::setX(const int x)
{
	_x = x;
}

void				Hardware::setY(const int y)
{
	_y = y;
}

/*
** Loggers
*/

void				Hardware::log(const std::string &txt)
{
	_buf += txt;
}

void				Hardware::log(char log)
{
	_buf += log;
}

/*
** reset
*/

void				Hardware::reset()
{
	_startTime = "";
	_endTime = "";
	_buf = "";
	_isWorking = false;
	_x = 0;
	_y = 0;
}

/*
** Getters
**/

bool				Hardware::isWorking()		const
{
	return _isWorking;
}

const std::string & Hardware::getStartTime()	const
{
	return _startTime;
}

const std::string & Hardware::getEndTime()		const
{
	return _endTime;
}

const HHOOK &		Hardware::getHandler()		const
{
	return _handler;
}

const std::string & Hardware::getLog()			const
{
	return _buf;
}

int					Hardware::getX()			const
{
	return _x;
}

int					Hardware::getY()			const
{
	return _y;
}