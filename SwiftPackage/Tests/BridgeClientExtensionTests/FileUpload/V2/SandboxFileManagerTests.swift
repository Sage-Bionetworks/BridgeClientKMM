// Created 8/1/23
// swift-tools-version:5.0

import XCTest
@testable import BridgeClientExtension

fileprivate let simulatorBaseDirectory = "/Users/foo/Library/Developer/CoreSimulator/Devices/ABE156AA-B189-4719-AB02-794DC169A014/data"
fileprivate let phoneBaseDirectory = "/var/mobile/Containers/Data/Application/258CADCB-F730-4DD4-AB13-4D8B23CDF93D"

final class SandboxFileManagerTests: XCTestCase {

    override func setUpWithError() throws {
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }

    override func tearDownWithError() throws {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
    }
    
    func createSandboxFileManager(_ simulator: Bool = true) -> SandboxFileManager {
        let manager = SandboxFileManager()
        manager.baseDirectory = simulator ? simulatorBaseDirectory : phoneBaseDirectory
        return manager
    }

    func testSandBoxRelativePath_Simulator() throws {
        let manager = createSandboxFileManager()
        let input = URL(string: "file://\(manager.baseDirectory)/Library/Application%20Support/StudyDataUploads/48B0BAEB-94C4-4158-953C-74AB0935E5FA")!
        let relativePath = manager.sandboxRelativePath(of: input)
        let expectedPath = "/Library/Application Support/StudyDataUploads/48B0BAEB-94C4-4158-953C-74AB0935E5FA"
        XCTAssertEqual(expectedPath, relativePath)
    }

    func testSandBoxRelativePath_Phone() throws {
        let manager = createSandboxFileManager(false)
        let input = URL(string: "file://\(manager.baseDirectory)/Library/Application%20Support/StudyDataUploads/48B0BAEB-94C4-4158-953C-74AB0935E5FA")!
        let relativePath = manager.sandboxRelativePath(of: input)
        let expectedPath = "/Library/Application Support/StudyDataUploads/48B0BAEB-94C4-4158-953C-74AB0935E5FA"
        XCTAssertEqual(expectedPath, relativePath)
    }
    
    func testFullyQualifiedPath_FromRelative_Simulator() throws {
        let manager = createSandboxFileManager()
        let input = "/Library/Application Support/StudyDataUploads/48B0BAEB-94C4-4158-953C-74AB0935E5FA"
        let fullPath = manager.fullyQualifiedPath(of: input)
        let expectedPath = "\(manager.baseDirectory)/Library/Application Support/StudyDataUploads/48B0BAEB-94C4-4158-953C-74AB0935E5FA"
        XCTAssertEqual(expectedPath, fullPath)
    }
    
    func testFullyQualifiedPath_FromFullPath_Simulator() throws {
        let manager = createSandboxFileManager()
        let input = "\(manager.baseDirectory)/Library/Application Support/StudyDataUploads/48B0BAEB-94C4-4158-953C-74AB0935E5FA"
        let fullPath = manager.fullyQualifiedPath(of: input)
        let expectedPath = "\(manager.baseDirectory)/Library/Application Support/StudyDataUploads/48B0BAEB-94C4-4158-953C-74AB0935E5FA"
        XCTAssertEqual(expectedPath, fullPath)
    }

}
