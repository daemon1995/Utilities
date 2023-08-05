// VSTrashCleaner.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <windows.h>
#include <string>
#include <experimental/filesystem>
#include <array>
#include <algorithm>
#include <vector>
namespace fs = std::experimental::filesystem;

int main(int argc, char** argv)
{


	if (argc > 1)
	{
		fs::path dirToClean(argv[1]);

		if (fs::is_regular_file(dirToClean))
		{
			dirToClean = dirToClean.parent_path();

		}

		if (fs::is_directory(dirToClean))
		{
			fs::recursive_directory_iterator dirIt(dirToClean);

			std::array<std::string, 16> listOfExtensions{ ".pch",".ipch", ".ipdb", ".iobj",".recipe",".obj",".pdb",".idb",".log",".tlog",
				".ilk", ".db", ".db-wal",".db-shm",".opendb",".lastbuildstate"};
			std::vector<std::string> fileListtoDelete(0);

			for (auto& entry : dirIt)
			{
				if (fs::is_regular_file(entry))
				{
					auto result = std::find(listOfExtensions.begin(), listOfExtensions.end(), entry.path().extension());

					if (result != listOfExtensions.end())
						fileListtoDelete.emplace_back(entry.path().string());
				}
			}

			if (!fileListtoDelete.empty())
			{
				for (auto& it : fileListtoDelete)
					std::cout << it << '\n';


				std::cout << "Remove all these files Y/N ?\n";
				char r;
				std::cin >> r;
				if (r == 'Y' || r == 'y')

				{
					for (auto& it : fileListtoDelete)
					{
						try
						{
							fs::remove(it);
						}
						catch (const std::exception& e)
						{
							std::cout << it << '\t' << e.what() << '\n';
						}

					}
					std::cout << "Removed\n";
				}
			}

		}

	}

	return 0;

}
