#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server)
    :search_server_(search_server)
{
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    std::vector<Document> result = search_server_.FindTopDocuments(raw_query, status);
    QueryResult query_result = { result.empty() };
    AddRequest(query_result);
    return result;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    std::vector<Document> result = search_server_.FindTopDocuments(raw_query);
    QueryResult query_result = { result.empty() };
    AddRequest(query_result);
    return result;
}

int RequestQueue::GetNoResultRequests() const {
    return count_of_null_results_;
}

void RequestQueue::AddRequest(QueryResult query_result) {
    requests_.push_back(query_result);
    if (requests_.back().null_result) {
        ++count_of_null_results_;
    }
    if (requests_.size() > min_in_day_) {
        if (requests_.front().null_result) {
            --count_of_null_results_;
        }
        requests_.pop_front();
    }
}