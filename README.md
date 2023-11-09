## csv_to_swift_endpoint_enum
A command line tool written in c++ that generates a swift enum for endpoints from a csv file


### Build
```
cmake . && make
```

### Run
`./csv_to_swift_endpoint_enum endpoints.csv > endpoints.swift`

### Sample csv
```
name,url,method
getendpoint1,https://example.com/api/endpoint1,GET
postendpoint2,https://api2.com/endpoint2,POST
putservice1,https://example.org/service1,PUT
getresource3,https://api3.net/resource3,GET
```

### Sample enum
```swift
import AsyncHTTPClient
import NIOHTTP1


public enum Endpoint {
    case getendpoint1
    case postendpoint2
    case putservice1
    case getresource3

    var url: String {
        switch self {
        case .getendpoint1: return "https://example.com/api/endpoint1"
        case .postendpoint2: return "https://api2.com/endpoint2"
        case .putservice1: return "https://example.org/service1"
        case .getresource3: return "https://api3.net/resource3"
        }
    }
    var httpMethod: HTTPMethod {
        switch self {
        case .getendpoint1: return .GET
        case .postendpoint2: return .POST
        case .putservice1: return .PUT
        case .getresource3: return .GET
        }
    }
    func requestBody() -> HTTPClient.Body? {
        switch self {
        case .getendpoint1: return nil
        case .postendpoint2: return nil
        case .putservice1: return nil
        case .getresource3: return nil
        }
    }
}
```