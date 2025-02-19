/*
 * @Author: hawrkchen
 * @Date: 2024-12-12 14:13:16
 * @Description: 
 * @FilePath: /omni_server/handler/omni_handler.cpp
 */

#include "omni_handler.hpp"


int Handler::preprocessor(HttpRequest* req, HttpResponse* res) 
{
    req->ParseBody();

    res->content_type = APPLICATION_JSON;

    return HTTP_STATUS_NEXT;
}

int Handler::error_handler(const HttpContextPtr& ctx)
{
    int err_code = ctx->response->status_code;
    return response_status(ctx, err_code);
}

// middleware
int Handler::auth_middleware(HttpRequest* req, HttpResponse* res)
{
    // TODO: implement authentication middleware
    return HTTP_STATUS_NEXT;
}


int Handler::ota_post_handler(HttpRequest* req, HttpResponse* res)
{
    if(req->content_type != APPLICATION_JSON) {
        return response_status(res, HTTP_STATUS_BAD_REQUEST, "Unsupported Media Type");
    }

    // print the request body
    hv::Json body_json = req->GetJson();
    std::cout << "OTA request body: " << body_json["name"] << std::endl; 
    //
    
    std::unique_ptr<OmniBase> task;
    if(body_json["type"] == "query") {
        task = OmniFactory::createOmniManager(OmniTask::TASK_OTA_QUERY);
    } else if(body_json["type"] == "upgrade") {
        task = OmniFactory::createOmniManager(OmniTask::TASK_OTA_UPGRADE);
    } else if(body_json["type"] == "rollback") {
        task = OmniFactory::createOmniManager(OmniTask::TASK_OTA_ROLLBACK);
    } else {
        return response_status(res, HTTP_STATUS_BAD_REQUEST, "Invalid Omni task type");
    }
    task->set_body_str(body_json.dump());

    // 应用主控
    task->process();

    auto [code, message, data] = task->get_http_resp();

    hv::Json response_json;
    response_json["message"] = message;
    response_json["code"] = code;
    response_json["data"] = data;

    res->content_type = APPLICATION_JSON;
    res->body = response_json.dump();

    return HTTP_STATUS_OK;
}

///=====================================
int Handler::response_status(const HttpContextPtr& ctx, int code, const char* message)
{
    response_status(ctx->response.get(), code, message);
    ctx->send();
    return code;
}

int Handler::response_status(const HttpResponseWriterPtr& writer, int code, const char* message)
{
    response_status(writer->response.get(), code, message);
    writer->End();
    return code;
}


int Handler::response_status(HttpResponse* res, int code, const char* message)
{
    if(message == nullptr) {
        message = http_status_str((enum http_status)code);
    }
    res->content_type = APPLICATION_JSON;


    hv::Json response_json;
    response_json["message"] = message;
    response_json["code"] = code;
    response_json["data"] = "";
    res->body = response_json.dump();

    return code;

}

