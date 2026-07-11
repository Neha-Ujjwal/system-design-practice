#pragma once

enum PaymentStatus {
  PENDING,
  COMPLETED,
  FAILED
};

class Payment {
  private:
    int paymentId;
    int paymentAmount;
    PaymentStatus paymentStatus;
  public:
    Payment(int paymentId, int paymentAmount, PaymentStatus paymentStatus){
      this->paymentId = paymentId;
      this->paymentAmount = paymentAmount;
      this->paymentStatus = paymentStatus;
    }
    
    int getPaymentId(){
      return paymentId;
    }
    
    int getPaymentAmount(){
      return paymentAmount;
    }

    PaymentStatus getPaymentStatus(){
      return paymentStatus;
    }

    void setPaymentId(int paymentId){
      this->paymentId = paymentId;
    }
    
    void setPaymentAmount(int paymentAmount){
      this->paymentAmount = paymentAmount;
    }

    void setPaymentStatus(PaymentStatus paymentStatus){
      this->paymentStatus = paymentStatus;
    }
};