#include "ProductCatalog.h"

namespace Services {

    void ProductCatalog::addProduct(std::shared_ptr<Models::Product> product) {
        if (product) {
            m_products.push_back(product);
        }
    }

    std::vector<std::shared_ptr<Models::Product>> ProductCatalog::getAllProducts() const {
        return m_products;
    }

    void ProductCatalog::clear() {
        m_products.clear();
    }

}