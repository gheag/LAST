
#include <iostream>
#include <SFML/Graphics.hpp>
#include "modbus.h"
#include <string>
#include <stdio.h>
#include <windows.h>


using namespace std;
using namespace sf;

namespace form {
	Font None;				// ����� ��������� �������������

	class Label {
	public:
		string text;	//�����
	protected:
		double x;		//���������� x
		double y;		//���������� y

		Text TXT;		//������������ �����

	public:
		Label(int _x = 0, int _y = 0, string _text = "�����")
		{
			int x = _x;
			int y = _y;
			text = _text;								// ��������� �����
			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(20); 					// � ��������, � �� ������!
		}
		Text displayText()
		{
			TXT.setString(text);						// ��������� � ��������� ����� ����������� �����
			return TXT;
		}
	};

	class Button : public Label {
	protected:
		double width;		// ������ ������
		double height;		// ������ ������
		RectangleShape BOX;	// ������� ������������� � �������� width, height
	public:
		Button(int _x = 0, int _y = 0, double _width = 150, double _height = 30, string _text = "������")
		{
			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;								// ��������� �����
			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(20); 					// � ��������, � �� ������!

			BOX.setSize(Vector2f(width, height));		// ������ ������
			BOX.setPosition(x, y);						// ���������� ������
			BOX.setFillColor(sf::Color(133, 133, 133));	// ���� ������
			BOX.setOutlineThickness(2);					// ������ X ��������
			BOX.setOutlineColor(Color(66, 66, 66));		// ���� �������
		}
		//�������� ������� �� ������
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {
				return  true;
			}
			else {
				return false;
			}
		}
		//����� ������
		Text displayText()
		{
			TXT.setString(text);  // ��������� � ��������� ����� ����������� �����
			return TXT;
		}
		//����� ������
		RectangleShape displayButton()
		{
			return BOX;
		}


	};

	class Input : public Button {
	protected:
		bool focus;
	public:
		Input(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "")
		{
			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;								// ��������� �����
			focus = false;								// ����� ���� �����

			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(20); 					// � ��������, � �� ������!
			TXT.setColor(Color::Black);					// ������������� ���� ���������� ������
			TXT.setPosition(x, y);						// ������� ������

			BOX.setSize(Vector2f(width, height));		// ������ ���� �����
			BOX.setPosition(x, y);						// ���������� ���� �����
			BOX.setFillColor(Color::White);	// ���� ������
		}
		//����� .reText( char ) �������� ����� ������ ������ ���� ������ Input
		void reText(char _tmp)
		{
			text.erase(text.size() - 1);

			if (_tmp != 8) {
				text += _tmp;
			}
			else {
				if (text.size() > 0) {
					text.erase(text.size() - 1);
				}

			}
			text += "|";
			TXT.setString(text);
		}

		// �������� ������ Input
		bool select()
		{
			return focus;
		}

		// ��������� ������ Input
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) { 	//���� ����� ������ ��� �������� Input...
				focus = true;																	   	// ����� true
				text += "|";																		// � ����� ������ �������� | (��� �� �������� ��� input � ������)
			}
			else {																				//...����� ���� ������� ��������� �� ��� ��������, ��...
				if (text.size() > 0) {																// �������� ���������� �������(����� ��������)
					if (text[text.size() - 1] == 124) {													// ���� ������ | ...
						text.erase(text.size() - 1);														// ... �� ������� ���
					}
				}
				focus = false;																		// ������������� ����� false
			}
			return focus;
		}

		//����� ������
		Text displayText()
		{
			TXT.setString(text);						// ��������� � ��������� ����� ����������� �����
			return TXT;
		}

		//����� ���� Input
		RectangleShape displayBOX()
		{
			return BOX;
		}

		//��� ����, ��� �� ������� ����� � ���� Ipnut ���������� ���������  readText() ������� ���������� string
		string readText()
		{
			if (text[text.size() - 1] == 124) { 	// ������� (���� ����) ������ |
				text.erase(text.size() - 1);
			}
			return text;
		}
	};

} /* namespace form */