﻿// Laba6Weather.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

void replace(std::string& str, const std::string from, std::string  to, int key)
{
    if (key == 1) to = to.substr(1, 10);
    else if(key==2) to = to.substr(1, 3);

    int startPos = str.find(from);
    if (startPos == std::string::npos) return;

    str.replace(startPos, from.length(), to);
}

/* "id": 1510514,
    "name": "Belogorsk",
    "state": "",
    "country": "RU",
    "coord": {
      "lon": 88.489723,
      "lat": 55.01778*/
void gen_response(const httplib::Request& req, httplib::Response& result)
{  /*переменная для виджета погоды*/
    std::string widget;
    httplib::Client cli("api.openweathermap.org", 80);
    auto res = cli.Get("/data/2.5/forecast?id=1510514&units=metric&APPID=852f923d23e30df95c2b94d2e5cdbf6b");
    json jsn;
   
    /*кодировка http, если 200 то все норм*/
    if (res && res->status == 200) jsn = json::parse(res->body);
    //считывание с файла в перм.
    std::ifstream stream("informer_template.html");
    if (!stream) { std::cout << "NoOpen"; }
    getline(stream, widget, '\0');
   
    stream.close();


    replace(widget, "{city.name}", jsn["city"]["name"].dump(), 1);
    for (int i = 0; i < 5; i++)
    {

        int start = jsn["list"][0]["dt"];
        for (int i = 0; i < 40; i++) // 5*8=40
        {
            if (jsn["list"][i]["dt"] >= start)
            {
                replace(widget, "{list.dt}", jsn["list"][i]["dt_txt"].dump(), 1);
                replace(widget, "{list.weather.icon}", jsn["list"][i]["weather"][0]["icon"].dump(), 2);
                replace(widget, "{list.main.temp}", jsn["list"][i]["main"]["temp"].dump(), 0);
                start += 86400;
            }
        }
    }
    // Команда set_content задаёт ответ сервера и тип ответа:
    result.set_content(widget, "text/html");
}


int main()
{
    httplib::Server svr;
    svr.Get("/", gen_response); // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
    svr.listen("localhost", 3000); // Запускаем сервер на localhost и порту 3000
}


