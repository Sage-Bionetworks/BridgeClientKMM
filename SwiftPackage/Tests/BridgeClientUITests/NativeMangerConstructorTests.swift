//

import Foundation
import BridgeClient

// Just tests that the constructors haven't changed and will build.
final class NativeMangerConstructorTests {
    
    func buildTimelineManager() {
        let _ = NativeTimelineManager(studyId: "preview", includeAllNotifications: false, alwaysIncludeNextDay: false) { _ in
        }
    }
}
