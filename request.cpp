#include <iostream>
#include <restclient-cpp/restclient.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class MkApi {

    private:
    string api_url;
    
    public:
    MkApi(string url){
        api_url = url;
    }

    auto request(string query){
        RestClient::Response r = RestClient::post(api_url, "application/json", query);
        return json::parse(r.body);
    }

    int sync(string last_analise_id){
        string api_ids = request("{\"query\": \"{analises(first: 1){data{id}}}\"}");
        auto j = json::parse(api_ids);
        int last_id = j["data"]["analises"]["data"][0]["id"];
        return last_id;
    }
};

int main(){
    string analises = "{\"query\": \"{analises{data{id datahora iq gordura proteina nu fccs lactose temperatura estabilidade desc_amostra local{nome} usuario{nome} }}}\"}";
    MkApi api("http://localhost:3000/graphql");
    auto response = api.request(analises);
    cout << response["data"]["analises"]["data"].dump(4) << endl;
}
