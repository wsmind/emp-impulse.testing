#include <common.hpp>
#include <cstdlib>
#include <cstring>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <lua.hpp>
#include <SFML/Graphics.hpp>

/**
 * \brief Image.
 *
 * The image may have a transparent margin around it, so the m* variables
 * define the sub-image (without such margin) inside the image.
 *
 * \code
 *   0                                            w
 * 0 +--------------------------------------------+
 *   |                                            |
 *   |                transparent                 |
 *   |                                            |
 *   |         mx                         mx+mw   |
 *   |      my +----------------------------+     |
 *   |         |                            |     |
 *   |         |                            |     |
 *   |         |                            |     |
 *   |         |                            |     |
 *   |         |      non-transparent       |     |
 *   |         |                            |     |
 *   |         |                            |     |
 *   |         |                            |     |
 *   |         |                            |     |
 *   |   my+mh +----------------------------+     |
 *   |                                            |
 *   |                                            |
 * h +--------------------------------------------+
 * \endcode
 */
struct Image
{
	/**
	 * \brief Pixel data.
	 */
	sf::Color *data;
	
	/**
	 * \brief X position in the resulting image.
	 */
	int x;
	
	/**
	 * \brief Y position in the resulting image.
	 */
	int y;
	
	/**
	 * \brief Width.
	 */
	int w;
	
	/**
	 * \brief Height.
	 */
	int h;
	
	/**
	 * \brief X position of the sub-image.
	 */
	int mx;
	
	/**
	 * \brief Y position of the sub-image.
	 */
	int my;
	
	/**
	 * \brief Width of the sub-image.
	 */
	int mw;
	
	/**
	 * \brief Height of the sub-image.
	 */
	int mh;
};

/**
 * \brief Sequence.
 */
struct Sequence
{
	/**
	 * \brief Name.
	 */
	std::string name;
	
	/**
	 * \brief Frame rate.
	 */
	float rate;
	
	/**
	 * \brief X offset.
	 */
	int ox;
	
	/**
	 * \brief Y offset.
	 */
	int oy;
	
	/**
	 * \brief Images.
	 */
	std::list<Image*> images;
	
	/**
	 * \brief Events.
	 */
	std::multimap<float, std::string> events;
};

/**
 * \brief Images of a sequence.
 *
 * To make the sort easier.
 */
static std::list<Image*> images;

/**
 * \brief Sequences.
 * 
 * For a single animation data.
 */
static std::list<Sequence> sequences;

/**
 * \brief Helper image.
 * 
 * Used to load each image and to create the new one.
 */
static sf::Image sfImage;

/**
 * \brief Maximum width within images.
 */
static int maxWidth;

/**
 * \brief Maximum height within images.
 */
static int maxHeight;

/**
 * \brief Compare function for sorting images.
 * \return true if i1 is larger than i2.
 * 
 * Sorts in descending order of size (width then height).
 */
static bool sortImages(const Image *i1, const Image *i2)
{
	return (i1->mw > i2->mw || i1->mh > i2->mh);
}

/**
 * \brief Paste an image into the global image.
 * \param image image data.
 */
static void pasteImage(const Image *image)
{
	for (int i = 0; i < image->mw; ++i)
	{
		for (int j = 0; j < image->mh; ++j)
		{
			sfImage.SetPixel(image->x + i, image->y + j, image->data[image->mx + i + image->w * (image->my + j)]);
		}
	}
}

/**
 * \brief Loads an image.
 * \param sequence image sequence.
 * \param file file name.
 * \return true on success, false otherwise.
 */
static bool loadImage(Sequence & sequence, const std::string & file)
{
	if (sfImage.LoadFromFile(file))
	{
		Image *image = new Image;
		
		image->w = sfImage.GetWidth();
		image->h = sfImage.GetHeight();
		
		image->data = new sf::Color[image->w * image->h];
		memcpy(image->data, sfImage.GetPixelsPtr(), image->w * image->h * sizeof(sf::Color));
		
		image->mx = 0;
		image->my = 0;
		image->mw = image->w;
		image->mh = image->h;
		
		int i;
		
		while (image->mw)
		{
			for (i = 0; i < image->mh; ++i)
			{
				if (image->data[image->mx + image->w * i].a > 0)
				{
					break;
				}
			}
			if (i < image->mh)
			{
				break;
			}
			++image->mx;
			--image->mw;
		}
		
		while (image->mw)
		{
			for (i = 0; i < image->mh; ++i)
			{
				if (image->data[image->mx + image->mw - 1 + image->w * i].a > 0)
				{
					break;
				}
			}
			if (i < image->mh)
			{
				break;
			}
			--image->mw;
		}
		
		while (image->mh)
		{
			for (i = 0; i < image->mw; ++i)
			{
				if (image->data[image->mx + i + image->w * image->my].a > 0)
				{
					break;
				}
			}
			if (i < image->mw)
			{
				break;
			}
			++image->my;
			--image->mh;
		}
		
		while (image->mh)
		{
			for (i = 0; i < image->mw; ++i)
			{
				if (image->data[image->mx + i + image->w * (image->my + image->mh - 1)].a > 0)
				{
					break;
				}
			}
			if (i < image->mw)
			{
				break;
			}
			--image->mh;
		}
		
		if (image->mw > maxWidth)
		{
			maxWidth = image->mw;
		}
		
		if (image->mh > maxHeight)
		{
			maxHeight = image->mh;
		}
		
		images.push_back(image);
		sequence.images.push_back(image);
		
		std::cout << "Image '" << file << "' loaded." << std::endl;
		return true;
	}
	
	return false;
}

static void writeUInt(std::ofstream & out, unsigned int value)
{
	out << (unsigned char)(value >> 24);
	out << (unsigned char)(value >> 16);
	out << (unsigned char)(value >> 8);
	out << (unsigned char)(value >> 0);
}

static void writeFloat(std::ofstream & out, float value)
{
	unsigned int val = *(unsigned int *)(void *)(&value);
	writeUInt(out, val);
}

static void writeString(std::ofstream & out, const std::string & str)
{
	int len = str.length();
	writeUInt(out, len);
	for (int i = 0; i < len; ++i)
	{
		out << str[i];
	}
}

int main(int argc, char **argv)
{
	lua_State *L = lua_open();
	
	for (int arg = 1; arg < argc; ++arg)
	{
		std::string file(argv[arg]);
		std::cout << "Processing file '" << file << "'." << std::endl;
		
		luaL_dofile(L, argv[arg]);
		
		lua_getglobal(L, "rate");
		float defaultRate = lua_tonumber(L, -1);
		lua_pop(L, 1);
		
		lua_getglobal(L, "sequences");
		if (lua_type(L, -1) != LUA_TTABLE)
		{
			std::cerr << "Error: 'sequences' undefined." << std::endl;
			continue;
		}
		
		images.clear();
		sequences.clear();
		maxWidth = 0;
		maxHeight = 0;
		
		// Iterates over each sequence
		for (lua_pushnil(L); lua_next(L, -2) != 0; lua_pop(L, 1))
		{
			if (!lua_isstring(L, -2) || lua_type(L, -1) != LUA_TTABLE)
			{
				std::cerr << "Error: bad sequence entry." << std::endl;
				continue;
			}
			
			Sequence sequence;
			sequence.name = std::string(lua_tostring(L, -2));
			
			std::cout << "Sequence '" << sequence.name << "' found." << std::endl;
			
			// Retrieve frame rate
			lua_getfield(L, -1, "rate");
			sequence.rate = lua_tonumber(L, -1);
			lua_pop(L, 1);
			if (sequence.rate == 0)
			{
				if (defaultRate != 0)
				{
					sequence.rate = defaultRate;
				}
				else
				{
					std::cerr << "Error: bad rate." << std::endl;
					continue;
				}
			}
			
			// Retrieves offset
			lua_getfield(L, -1, "offset");
			if (lua_type(L, -1) != LUA_TTABLE)
			{
				lua_pop(L, 1);
				std::cerr << "Error: bad rate." << std::endl;
				continue;
			}
			lua_getfield(L, -1, "x");
			sequence.ox = lua_tonumber(L, -1);
			lua_getfield(L, -2, "y");
			sequence.oy = lua_tonumber(L, -1);
			lua_pop(L, 3);
			
			// Retrieves image paths
			lua_getfield(L, -1, "path");
			if (lua_type(L, -1) == LUA_TTABLE)
			{
				int index = 1;
				
				for (;;++index)
				{
					lua_pushnumber(L, index);
					lua_gettable(L, -2);
					if (!lua_isstring(L, -1))
					{
						std::cerr << "Error: image " << index << " is not a path." << std::endl;
					}
					else
					{
						std::string file(lua_tostring(L, -1));
						if (!loadImage(sequence, file))
						{
							std::cout << "Error: unable to load image '" << file << "'." << std::endl;
						}
					}
					lua_pop(L, 1);
				}
				
				lua_pop(L, 1);
			}
			else if (lua_isstring(L, -1))
			{
				std::string path(lua_tostring(L, -1));
				lua_pop(L, 1);
				if (path.find('%') != std::string::npos)
				{
					int index = 1;
					
					for (;;++index)
					{
						char file[256];
						sprintf(file, path.c_str(), index);;
						if (!loadImage(sequence, file))
						{
							std::cout << "Unable to load image '" << file << "', continuing..." << std::endl;
							break;
						}
					}
				}
				else if (!loadImage(sequence, path))
				{
					std::cerr << "Error: unable to load image '" << path << "'." << std::endl;
					continue;
				}
			}
			else
			{
				std::cerr << "Error: bad path." << std::endl;
				lua_pop(L, 1);
				continue;
			}
			
			// Retrieves events (optional)
			lua_getfield(L, -1, "events");
			if (lua_type(L, -1) == LUA_TTABLE)
			{
				for (lua_pushnil(L); lua_next(L, -2) != 0; lua_pop(L, 1))
				{
					if (!lua_isnumber(L, -2))
					{
						std::cerr << "Error: bad event key." << std::endl;
						continue;
					}
					if (lua_type(L, -1) == LUA_TTABLE)
					{
						int index = 1;
						
						for (;;++index)
						{
							lua_pushnumber(L, index);
							lua_gettable(L, -2);
							if (!lua_isstring(L, -1))
							{
								std::cerr << "Error: bad event value." << std::endl;
							}
							else
							{
								sequence.events.insert(std::pair<float, std::string>(lua_tonumber(L, -3), std::string(lua_tostring(L, -1))));
							}
							lua_pop(L, 1);
						}
					}
					else if (lua_isstring(L, -1))
					{
						sequence.events.insert(std::pair<float, std::string>(lua_tonumber(L, -2), std::string(lua_tostring(L, -1))));
					}
					else
					{
						std::cerr << "Error: bad event value." << std::endl;
					}
				}
			}
			
			sequences.push_back(sequence);
			
			lua_pop(L, 1);
		}
		
		// Merges images
		if (images.size() > 0)
		{
			int n = images.size();
			
			// Finds tile count
			int w = 1;
			while (w * w < n)
			{
				++w;
			}
			int h = ceil(n / (float)w);
			
			std::cout << "Resulting image: horizontal tiles = " << w << ", vertical tiles = " << h << "." << std::endl;
			
			images.sort(sortImages);
			
			int width = w * maxWidth;
			int height = h * maxHeight;
			
			sfImage.Create(width, height);
			
			// Pastes images
			int i = 0;
			for (std::list<Image*>::iterator it = images.begin(); it != images.end(); ++it, ++i)
			{
				(*it)->x = (i % w) * maxWidth;
				(*it)->y = (i / w) * maxHeight;
				pasteImage(*it);
			}
			
			if (!sfImage.SaveToFile(file + ".png"))
			{
				std::cerr << "Error: unable to save resulting image." << std::endl;
			}
			
			// Generates animation data
			std::ofstream data((file + ".data").c_str(), std::ios_base::in | std::ios::binary);
			if (data.is_open())
			{
				writeUInt(data, sequences.size());
				
				for (std::list<Sequence>::iterator it = sequences.begin(); it != sequences.end(); ++it)
				{
					Sequence & sequence = *it;
					writeString(data, sequence.name);
					
					writeFloat(data, 1 / sequence.rate);
					
					writeUInt(data, sequence.images.size());
					for (std::list<Image*>::iterator it2 = sequence.images.begin(); it2 != sequence.images.end(); ++it2)
					{
						writeUInt(data, (*it2)->x);
						writeUInt(data, (*it2)->y);
						writeUInt(data, (*it2)->x + (*it2)->mw);
						writeUInt(data, (*it2)->y + (*it2)->mh);
						writeUInt(data, sequence.ox - (*it2)->mx);
						writeUInt(data, sequence.oy - (*it2)->my);
					}
					
					writeUInt(data, sequence.events.size());
					for (std::multimap<float, std::string>::iterator it2 = sequence.events.begin(); it2 != sequence.events.end(); ++it2)
					{
						writeFloat(data, it2->first);
						writeString(data, it2->second);
					}
				}
				
			}
			else
			{
				std::cerr << "Error: unable to save animation data." << std::endl;
			}
			
			for (std::list<Image*>::iterator it = images.begin(); it != images.end(); ++it)
			{
				delete [] (*it)->data;
				delete (*it);
			}
			
		}
		
	}
	
	lua_close(L);
	
	return EXIT_SUCCESS;
}
