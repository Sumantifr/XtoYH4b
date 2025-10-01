void check_path()
{

    std::string file_path = std::filesystem::current_path().string();

    std::cout << "Current path: " << file_path << std::endl;

}
