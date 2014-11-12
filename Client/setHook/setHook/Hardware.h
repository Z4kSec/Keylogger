#pragma once

#include <windows.h>
#include <string>

class Hardware
{
public:
	Hardware(int idHook);

	bool hook(HOOKPROC lpfn);
	void unHook();

	void startWorking(const std::string &time);
	void endWorking(const std::string &time);
	void setX(const int x);
	void setY(const int y);

	void log(const std::string &txt);
	void log(char txt);

	bool isWorking()						const;

	const std::string & getStartTime()		const;
	const std::string & getEndTime()		const;
	const HHOOK &		getHandler()		const;
	const std::string & getLog()			const;
	int					getX()				const;
	int					getY()				const;

	void reset();

private:
	int			_idHook;
	HHOOK		_handler;

	bool		_isWorking;
	int			_x;
	int			_y;

	std::string _startTime;
	std::string _endTime;
	std::string _buf;
};