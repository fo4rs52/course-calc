#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "Entity.h"

namespace Models {

    class UserProfile : public Entity {
    private:
        double m_weight;
        double m_height;
        int m_age;
        bool m_isMale;

    public:
        UserProfile(double w = 70.0, double h = 170.0, int a = 25, bool male = true);

        double weight() const { return m_weight; }
        double height() const { return m_height; }
        int age() const { return m_age; }
        bool isMale() const { return m_isMale; }

        QJsonObject toJson() const override;
        void fromJson(const QJsonObject& json) override;
        QString getDisplayName() const override;
    };

} 
#endif