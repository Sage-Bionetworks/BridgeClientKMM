//
//  LogoImage.swift
//

import SwiftUI

#if os(iOS)
typealias BCUImage = UIImage
#else
typealias BCUImage = NSImage
#endif

public struct LogoImage: View {
    @StateObject var imageLoader: ImageLoader = .init()
    
    private let url: String?

    public init(url: String?) {
        self.url = url
    }

    public var body: some View {
        logoImage()
            .resizable()
            .aspectRatio(contentMode: .fit)
            .frame(height:80)
            .frame(maxWidth: .infinity, alignment: .center)
            .onAppear {
                imageLoader.onAppear(urlString: self.url)
            }
    }
    
    func logoImage() -> Image {
#if os(iOS)
        Image(uiImage: imageLoader.image)
#else
        Image(nsImage: imageLoader.image)
#endif
    }
    
    class ImageLoader: ObservableObject {
        @Published var image: BCUImage = .init()

        func onAppear(urlString: String?) {
            guard let urlString = urlString,
                  let url = URL(string: urlString)
            else {
                return
            }
            let task = URLSession.shared.dataTask(with: url) { data, response, error in
                guard let data = data, let downloadedImage = BCUImage(data: data)
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
