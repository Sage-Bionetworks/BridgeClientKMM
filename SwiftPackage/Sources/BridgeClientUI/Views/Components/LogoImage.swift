//
//  LogoImage.swift
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
