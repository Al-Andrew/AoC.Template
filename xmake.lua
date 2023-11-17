add_rules("mode.debug", "mode.release")

add_requires("cxxopts")
add_requires("cpp-httplib", {configs = {ssl = true}})
set_languages("c++20")
set_warnings("all")

for _, dir in ipairs(os.dirs("src/*")) do
    target(string.match(dir, "[^\\/]+$"))
        set_kind("binary")
        add_files(dir .. "/*.cpp")

        add_packages("cxxopts", "cpp-httplib", "openssl")
    target_end()
end