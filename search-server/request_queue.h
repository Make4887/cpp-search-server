#pragma once
#include "search_server.h"
#include "document.h"
#include <deque>
#include <string>
#include <vector>

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        std::vector<Document> result = search_server_.FindTopDocuments(raw_query, document_predicate);
        QueryResult query_result = { result.empty() };
        AddRequest(query_result);
        return result;
    }

    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);

    std::vector<Document> AddFindRequest(const std::string& raw_query);

    int GetNoResultRequests() const;

private:
    struct QueryResult {
        bool null_result;
    };

    std::deque<QueryResult> requests_;
    int count_of_null_results_ = 0;
    const static int min_in_day_ = 1440;
    const SearchServer& search_server_;

    void AddRequest(QueryResult query_result);
};