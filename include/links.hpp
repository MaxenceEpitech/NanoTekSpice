/*
 ** EPITECH PROJECT , 2018
 ** NanoTekSpice2
 ** File description :
 ** 	File Name : links.h Author : maxence.fourrier Date : 1 mars 2018
 */

#ifndef SRC_LINKS_HPP_
#define SRC_LINKS_HPP_

#include <string>

namespace nts {
	class links {
	public:
		links();
		links(size_t idLink1, size_t idLink2, std::string link1,
				std::string link2);
		~links();
		size_t getIdLink1() const;
		size_t getIdLink2() const;
		const std::string& getLink1() const;
		const std::string& getLink2() const;
		void setIdLink1(size_t idLink1);
		void setIdLink2(size_t idLink2);
		void setLink1(const std::string& link1);
		void setLink2(const std::string& link2);

		void print();

	private:
		size_t _idLink1;
		size_t _idLink2;
		std::string _link1;
		std::string _link2;
	};
}

#endif /* SRC_LINKS_HPP_ */
