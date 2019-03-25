#include <iostream>
#include "../../PlayerInfo/PlayerInfo.h"
class Info {
	public:
		Info(PlayerInfo& playerInfo);
		Info();
		

		void setID(const std::string& id);
		void setAvatar(char avatar);
		void setAlive(bool flag);
		void setLost(bool flag);
		void setPoints(DWORD points);
		void increasePoints(DWORD value);
		void setColor(DWORD color);

		std::string getID();
		char getAvatar();
		bool isAlive();
		bool hasLost();
		DWORD getPoints();
		DWORD getColor();

		bool operator==(const Info& other) const;
	private:
		std::string id;
		char avatar;
		bool alive;
		bool lost;
		DWORD points;
		DWORD color;
	};
