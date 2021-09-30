//
//  LogoImage.swift
//
//  Copyright © 2021 Sage Bionetworks. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1.  Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2.  Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//
// 3.  Neither the name of the copyright holder(s) nor the names of any contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission. No license is granted to the trademarks of
// the copyright holders even if such marks are included in this software.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

import SwiftUI

public struct LogoImage: View {
    @StateObject var imageLoader: ImageLoader = .init()
    
    private let url: String?

    public init(url: String?) {
        self.url = url
    }

    public var body: some View {
        Image(uiImage: imageLoader.image)
            .resizable()
            .aspectRatio(contentMode: .fit)
            .frame(height:80)
            .frame(maxWidth: .infinity, alignment: .center)
            .onAppear {
                imageLoader.onAppear(urlString: self.url)
            }
    }
    
    class ImageLoader: ObservableObject {
        @Published var image: UIImage = .init()

        func onAppear(urlString: String?) {
            guard let urlString = urlString,
                  let url = URL(string: urlString)
            else {
                return
            }
            let task = URLSession.shared.dataTask(with: url) { data, response, error in
                guard let data = data, let downloadedImage = UIImage(data: data)
                else {
                    return
                }
                DispatchQueue.main.async {
                    self.image = downloadedImage
                }
            }
            task.resume()
        }
    }
}

struct LogoImage_Previews: PreviewProvider {
    static var previews: some View {
        LogoImage(url: "https://docs.sagebridge.org/5rht4Xajwu2N69EPlHXfjT-Y.1632172103361")
    }
}
