import Foundation
import AsyncDisplayKit
import Display

public final class ContextContentContainingNode: ASDisplayNode {
    public let contentNode: ContextContentNode
    public var contentRect: CGRect = CGRect()
    public var isExtractedToContextPreview: Bool = false
    public var isExtractedToContextPreviewUpdated: ((Bool) -> Void)?
    public var updateAbsoluteRect: ((CGRect, CGSize) -> Void)?
    public var applyAbsoluteOffset: ((CGFloat, ContainedViewLayoutTransitionCurve, Double) -> Void)?
    public var applyAbsoluteOffsetSpring: ((CGFloat, Double, CGFloat) -> Void)?
    
    public override init() {
        self.contentNode = ContextContentNode()
        
        super.init()
        
        self.addSubnode(self.contentNode)
    }
}

public final class ContextContentNode: ASDisplayNode {
}