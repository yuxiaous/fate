<GameProjectFile>
  <PropertyGroup Type="Scene" Name="begin" ID="c56596ea-4b80-4598-94a6-89b9cf0b9bc5" Version="2.2.9.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="8" Speed="0.1667" ActivedAnimationName="blink">
        <Timeline ActionTag="-183604940" Property="Position">
          <PointFrame FrameIndex="8" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-183604940" Property="Scale">
          <ScaleFrame FrameIndex="8" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-183604940" Property="RotationSkew">
          <ScaleFrame FrameIndex="8" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-183604940" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_2.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="1" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_3.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="2" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_4.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_5.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="4" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_6.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="5" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_7.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="6" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_8.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="7" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_9.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="8" Tween="False">
            <TextureFile Type="MarkedSubImage" Path="images/ui/logo_10.png" Plist="images/ui/logo.plist" />
          </TextureFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="blink" StartIndex="0" EndIndex="30">
          <RenderColor A="255" R="188" G="143" B="143" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="root" Tag="94" ctype="GameNodeObjectData">
        <Size X="1136.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="sp_background" ActionTag="1311981216" Tag="68" IconVisible="False" RightMargin="-119.0000" ctype="SpriteObjectData">
            <Size X="1255.0000" Y="640.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="images/ui/beijing02.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_enter" ActionTag="722048707" Tag="96" IconVisible="False" TouchEnable="True" FontSize="22" Scale9Width="1" Scale9Height="1" ctype="ButtonObjectData">
            <Size X="1136.0000" Y="640.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <TextColor A="255" R="255" G="255" B="255" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="sp_saber" ActionTag="-1784074810" Tag="195" IconVisible="False" RightMargin="542.0000" ctype="SpriteObjectData">
            <Size X="594.0000" Y="640.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="images/ui/beijing03.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="sp_logo" ActionTag="810824774" Tag="125" IconVisible="False" LeftMargin="697.0000" RightMargin="83.0000" TopMargin="41.6000" BottomMargin="452.4000" ctype="SpriteObjectData">
            <Size X="356.0000" Y="146.0000" />
            <Children>
              <AbstractNodeData Name="sp_logo_bling" ActionTag="-183604940" Tag="67" IconVisible="False" RightMargin="352.0000" TopMargin="142.0000" ctype="SpriteObjectData">
                <Size X="4.0000" Y="4.0000" />
                <AnchorPoint />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="MarkedSubImage" Path="images/ui/logo_10.png" Plist="images/ui/logo.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.6000" />
            <Position X="875.0000" Y="540.0000" />
            <Scale ScaleX="1.2000" ScaleY="1.2000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7702" Y="0.8438" />
            <PreSize />
            <FileData Type="MarkedSubImage" Path="images/ui/logo.png" Plist="images/ui/logo.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sprite_1" ActionTag="1966600719" Tag="192" IconVisible="False" LeftMargin="568.0000" RightMargin="280.0000" TopMargin="499.5000" BottomMargin="101.5000" FlipX="True" ctype="SpriteObjectData">
            <Size X="288.0000" Y="39.0000" />
            <Children>
              <AbstractNodeData Name="Sprite_2" ActionTag="1144542390" Tag="193" IconVisible="False" LeftMargin="-288.0000" RightMargin="288.0000" ctype="SpriteObjectData">
                <Size X="288.0000" Y="39.0000" />
                <AnchorPoint ScaleX="1.0000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_171.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Sprite_3" ActionTag="-1776354089" Tag="194" IconVisible="False" LeftMargin="-141.5000" RightMargin="146.5000" TopMargin="4.5000" BottomMargin="5.5000" ctype="SpriteObjectData">
                <Size X="283.0000" Y="29.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="20.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition Y="0.5128" />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_172.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleY="0.5000" />
            <Position X="568.0000" Y="121.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.1891" />
            <PreSize />
            <FileData Type="Normal" Path="images/ui/ui_171.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_about" ActionTag="-1290547249" Tag="277" IconVisible="False" LeftMargin="40.0000" RightMargin="1032.0000" TopMargin="559.0000" BottomMargin="17.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="34" Scale9Height="42" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
            <Size X="64.0000" Y="64.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="72.0000" Y="49.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0634" Y="0.0766" />
            <PreSize X="0.0563" Y="0.1000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="images/button/button_88.png" Plist="" />
            <PressedFileData Type="Normal" Path="images/button/button_88.png" Plist="" />
            <NormalFileData Type="Normal" Path="images/button/button_72.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_exit" ActionTag="-1105166693" Tag="364" IconVisible="False" LeftMargin="1044.3223" RightMargin="27.6777" TopMargin="559.0000" BottomMargin="17.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="34" Scale9Height="42" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
            <Size X="64.0000" Y="64.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1076.3223" Y="49.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9475" Y="0.0766" />
            <PreSize X="0.0563" Y="0.1000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="images/button/button_80.png" Plist="" />
            <PressedFileData Type="Normal" Path="images/button/button_80.png" Plist="" />
            <NormalFileData Type="Normal" Path="images/button/button_79.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_more_game" ActionTag="-241985057" Tag="12" IconVisible="False" LeftMargin="40.0000" RightMargin="1032.0000" TopMargin="469.0000" BottomMargin="107.0000" TouchEnable="True" FontSize="14" ButtonText="Button" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="34" Scale9Height="42" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
            <Size X="64.0000" Y="64.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="72.0000" Y="139.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0634" Y="0.2172" />
            <PreSize X="0.0563" Y="0.1000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="images/button/button_87.png" Plist="" />
            <PressedFileData Type="Normal" Path="images/button/button_87.png" Plist="" />
            <NormalFileData Type="Normal" Path="images/button/button_86.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>