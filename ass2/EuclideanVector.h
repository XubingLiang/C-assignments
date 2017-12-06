#include <string>

class EulideanVector {
public:
  EulideanVector();
  EulideanVector(const std::string& manufacturer, unsigned numSeats);
  EulideanVector(const EulideanVector&);
  EulideanVector(EulideanVector&&);
  EulideanVector& operator=(const EulideanVector&) = default;
  EulideanVector& operator=(EulideanVector&&) = default;
  ~EulideanVector() noexcept;

  const std::string& getManufacturer() const;

  static unsigned getObjectCount();

private:
  std::string _manufacturer;
  unsigned int _numSeats;

  static unsigned numCars;
};